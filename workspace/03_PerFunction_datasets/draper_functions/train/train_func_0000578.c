BigDecimal_div2(int argc, VALUE *argv, VALUE self)
{
    ENTER(5);
    VALUE b,n;
    int na = rb_scan_args(argc,argv,"11",&b,&n);
    if(na==1) {
       Real *div=NULL;
       Real *mod;
       if(BigDecimal_DoDivmod(self,b,&div,&mod)) {
	  return BigDecimal_to_i(ToValue(div));
       }
       return DoSomeOne(self,b,rb_intern("div"));
    } else {
       SIGNED_VALUE ix = GetPositiveInt(n);
       if (ix == 0) return BigDecimal_div(self, b);
       else {
          Real *res=NULL;
          Real *av=NULL, *bv=NULL, *cv=NULL;
          size_t mx = (ix+VpBaseFig()*2);
          size_t pl = VpSetPrecLimit(0);

          GUARD_OBJ(cv,VpCreateRbObject(mx,"0"));
          GUARD_OBJ(av,GetVpValue(self,1));
          GUARD_OBJ(bv,GetVpValue(b,1));
          mx = av->Prec + bv->Prec + 2;
          if(mx <= cv->MaxPrec) mx = cv->MaxPrec+1;
          GUARD_OBJ(res,VpCreateRbObject((mx * 2  + 2)*VpBaseFig(), "#0"));
          VpDivd(cv,res,av,bv);
          VpSetPrecLimit(pl);
          VpLeftRound(cv,VpGetRoundMode(),ix);
          return ToValue(cv);
       }
    }
}
