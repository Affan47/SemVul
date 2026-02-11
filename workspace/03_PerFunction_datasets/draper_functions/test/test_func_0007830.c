putstring(LVAL fptr, LVAL str)
{
    unsigned char *p;
    int ch;


    for (p = getstring(str); (ch = *p) != '\0'; ++p)
        xlputc(fptr,ch);
}
