BigDecimal_mod(VALUE self, VALUE r)
{
    ENTER(3);
    Real *div=NULL, *mod=NULL;

    if(BigDecimal_DoDivmod(self,r,&div,&mod)) {
	SAVE(div); SAVE(mod);
	return ToValue(mod);
    }
    return DoSomeOne(self,r,'%');
}
