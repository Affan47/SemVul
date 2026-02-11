xrdchar(void)
{
    LVAL fptr;
    int ch;


    fptr = (moreargs() ? xlgetfile() : getvalue(s_stdin));
    xllastarg();


    return ((ch = xlgetc(fptr)) == EOF ? NIL : cvchar(ch));
}
