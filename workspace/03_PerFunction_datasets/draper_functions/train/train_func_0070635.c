x1macroexpand(void)
{
    LVAL form,fun,args;


    xlstkcheck(2);
    xlsave(fun);
    xlsave(args);


    form = xlgetarg();
    xllastarg();


    if (consp(form)) {
        fun = car(form);
        args = cdr(form);
        if (symbolp(fun) && fboundp(fun)) {
            fun = xlgetfunction(fun);
            macroexpand(fun,args,&form);
        }
    }


    xlpopn(2);
    return (form);
}
