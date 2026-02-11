xlpeek(LVAL fptr)
{
    LVAL lptr, cptr=NULL;
    int ch;


    if (fptr == NIL)
        ch = EOF;


    else if (ustreamp(fptr)) {
        if ((lptr = gethead(fptr)) == NIL)
            ch = EOF;
        else {
            if (!consp(lptr) || (cptr = car(lptr)) == NIL || !charp(cptr))
                xlfail("bad stream");
            ch = getchcode(cptr);
        }
    }


    else {
        ch = xlgetc(fptr);
        setsavech(fptr,ch);
    }


    return (ch);
}
