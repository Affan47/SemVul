nextch(LVAL fptr)
{
    int ch;


    while ((ch = xlgetc(fptr)) != EOF && isspace(ch))
        ;
    xlungetc(fptr,ch);
    return (ch);
}
