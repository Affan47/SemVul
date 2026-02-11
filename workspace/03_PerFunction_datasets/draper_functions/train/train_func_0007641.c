bt_translate_inst(X86Assembler *pbuf, byteptr pc, bdecode *inst) {
    switch(OP_CLASS(inst->opcode)) {
    case CLASS_ARITH:
        bt_translate_arith(pbuf, pc, inst);
        break;
    case CLASS_ARITHC:
        bt_translate_arithc(pbuf, pc, inst);
        break;
    default:
        bt_translate_other(pbuf, pc, inst);
        break;
    }
    return;
}
