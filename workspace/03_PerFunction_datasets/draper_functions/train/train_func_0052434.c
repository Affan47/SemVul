xlgetprop(LVAL sym, LVAL prp)
{
    LVAL p;
    return ((p = findprop(sym,prp)) ? car(p) : NIL);
}
