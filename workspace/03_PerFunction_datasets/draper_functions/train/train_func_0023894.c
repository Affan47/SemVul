MoveToMemoryFromStack(unsigned size)
{
    AddCmd(ASM_POP, REG_EBX);
    for (int i = 0; i < size; i += 4)
    {
        AddCmd(ASM_POP, REG_EAX);
        AddCmd(ASM_MOV, REG_EAX, AsmMemory(REG_EBX, i));
    }
}
