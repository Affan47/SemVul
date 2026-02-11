xleval(LVAL expr)
{

    if (--xlsample <= 0) {
        xlsample = SAMPLE;
        oscheck();
    }


    if (getvalue(s_evalhook))
        return (evalhook(expr));


    if (null(expr))
        return (NIL);


    switch (ntype(expr)) {
    case CONS:
        return (evform(expr));
    case SYMBOL:
        return (xlgetvalue(expr));
    default:
        return (expr);
    }
}
