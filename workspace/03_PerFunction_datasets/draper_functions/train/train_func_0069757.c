xloop(void)
{
    LVAL *argv,arg,val;
    XLCONTEXT cntxt;
    int argc;


    xlsave1(arg);


    xlbegin(&cntxt,CF_RETURN,NIL);
    if (setjmp(cntxt.c_jmpbuf))
        val = xlvalue;
    else
        for (argv = xlargv, argc = xlargc; ; xlargv = argv, xlargc = argc)
            while (moreargs()) {
                arg = nextarg();
                if (consp(arg))
                    xleval(arg);
            }
    xlend(&cntxt);


    xlpop();


    return (val);
}
