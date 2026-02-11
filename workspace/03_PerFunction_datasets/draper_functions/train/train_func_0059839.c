parseStub (git_uint32 * pc, int mode, Label discardOp)
{
    git_uint32 value;
    switch (mode)
    {
        case 0x0:
            goto store_discard;
        case 0x5:
            value = memRead8(*pc);
            *pc += 1;
            goto store_addr;
        case 0x6:
            value = memRead16(*pc);
            *pc += 2;
            goto store_addr;
        case 0x7:
            value = memRead32(*pc);
            *pc += 4;
            goto store_addr;
        case 0x8:
            goto store_stack;
        case 0x9:
            value = memRead8(*pc);
            *pc += 1;
            goto store_local;
        case 0xA:
            value = memRead16(*pc);
            *pc += 2;
            goto store_local;
        case 0xB:
            value = memRead32(*pc);
            *pc += 4;
            goto store_local;
        case 0xD:
            value = memRead8(*pc) + gRamStart;
            *pc += 1;
            goto store_addr;
        case 0xE:
            value = memRead16(*pc) + gRamStart;
            *pc += 2;
            goto store_addr;
        case 0xF:
            value = memRead32(*pc) + gRamStart;
            *pc += 4;
            goto store_addr;

        store_discard:
            emitCode (discardOp);
            break;
        store_stack:
            emitCode (discardOp + (label_call_stub_stack - label_call_stub_discard));
            break;
        store_addr:
            emitCode (discardOp + (label_call_stub_addr - label_call_stub_discard));
            emitData (value);
            break;
        store_local:
            emitCode (discardOp + (label_call_stub_local - label_call_stub_discard));
            emitData (value);
            break;
    }


    emitData (*pc);


    nextInstructionIsReferenced ();
}
