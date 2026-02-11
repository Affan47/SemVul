xchar(void)
{
    LVAL str,num;
    int n;


    str = xlgastring();
    num = xlgafixnum();
    xllastarg();


    if ((n = (int)getfixnum(num)) < 0 || n >= getslength(str) - 1)
        xlerror("index out of range",num);


    return (cvchar(getstring(str)[n]));
}
