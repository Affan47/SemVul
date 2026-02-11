GenValueInStack(AsmCode& asm_code) const
{
    if (by_ref || type->GetSize() == 4)
        asm_code.AddCmd(ASM_PUSH, AsmMemory(REG_EBP, offset));
    else
    {
        GenAdrInStack(asm_code);
        asm_code.PushMemory(type->GetSize());
    }
}
