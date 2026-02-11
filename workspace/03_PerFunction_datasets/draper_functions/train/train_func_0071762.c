ObtainLabels(AsmCode& asm_code)
{
    break_label = asm_code.GenLabel("break");
    continue_label = asm_code.GenLabel("continue");;
}
