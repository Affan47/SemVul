BigDecimal_div(VALUE self, VALUE r)

{
    ENTER(5);
    Real *c=NULL, *res=NULL, *div = NULL;
    r = BigDecimal_divide(&c, &res, &div, self, r);
    if(r!=(VALUE)0) return r;
    SAVE(c);SAVE(res);SAVE(div);


    if(VpHasVal(div)) {
	VpInternalRound(c, 0, c->frac[c->Prec-1], (BDIGIT)(VpBaseVal()*(BDIGIT_DBL)res->frac[0]/div->frac[0]));
    }
    return ToValue(c);
}
