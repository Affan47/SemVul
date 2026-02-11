flatsize(int pflag)
{
    LVAL val;


    val = xlgetarg();
    xllastarg();


    xlfsize = 0;
    xlprint(NIL,val,pflag);


    return (cvfixnum((FIXTYPE)xlfsize));
}
