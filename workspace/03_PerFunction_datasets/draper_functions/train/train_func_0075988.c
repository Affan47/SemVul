NextLine(char *pc)
{
    while (*pc != 0)
    {
        if (pc[0] == '\n' && pc[1] == '\r') return pc + 2;
        else if (pc[0] == '\n') return pc + 1;
        pc++;
    }
    return pc;
}
