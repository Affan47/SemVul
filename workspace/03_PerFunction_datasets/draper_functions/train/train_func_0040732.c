remover(l,r,o)
Text l;
Type r;
Int  o; {
    Tyvar *tyv;
    Int    beta       = newTyvars(1);
    tyvar(beta)->kind = ROW;
#if DEBUG_TYPES
    Printf("removing %s from",textToStr(l));
    printType(stdout,debugType(r,o));
    Putchar('\n');
#endif
    expandSynFully(&r,&o);
    deRef(tyv,r,o);
    if (tyv || !isAp(r) || !isAp(fun(r)) || !isExt(fun(fun(r))))
	internal("remover");
    if (l==extText(fun(fun(r))))
	r = extRow(r);
    else
	r = ap(fun(r),mkInt(remover(l,extRow(r),o)));
    bindTv(beta,r,o);
    return beta;
}
