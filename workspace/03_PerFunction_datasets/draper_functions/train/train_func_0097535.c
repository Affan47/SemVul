xcharint(void)
{
    LVAL arg;
    arg = xlgachar();
    xllastarg();
    return (cvfixnum((FIXTYPE)getchcode(arg)));
}
