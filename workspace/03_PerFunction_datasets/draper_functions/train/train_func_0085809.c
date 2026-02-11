BigDecimal_divremain(VALUE self, VALUE r, Real **dv, Real **rv)
{
    ENTER(10);
    size_t mx;
    Real *a=NULL, *b=NULL, *c=NULL, *res=NULL, *d=NULL, *rr=NULL, *ff=NULL;
    Real *f=NULL;

    GUARD_OBJ(a,GetVpValue(self,1));
    if (RB_TYPE_P(r, T_FLOAT)) {
	b = GetVpValueWithPrec(r, DBL_DIG+1, 1);
    }
    else if (RB_TYPE_P(r, T_RATIONAL)) {
	b = GetVpValueWithPrec(r, a->Prec*VpBaseFig(), 1);
    }
    else {
	b = GetVpValue(r,0);
    }

    if(!b) return DoSomeOne(self,r,rb_intern("remainder"));
    SAVE(b);

    mx  =(a->MaxPrec + b->MaxPrec) *VpBaseFig();
    GUARD_OBJ(c  ,VpCreateRbObject(mx, "0"));
    GUARD_OBJ(res,VpCreateRbObject((mx+1) * 2 +(VpBaseFig() + 1), "#0"));
    GUARD_OBJ(rr ,VpCreateRbObject((mx+1) * 2 +(VpBaseFig() + 1), "#0"));
    GUARD_OBJ(ff ,VpCreateRbObject((mx+1) * 2 +(VpBaseFig() + 1), "#0"));

    VpDivd(c, res, a, b);

    mx = c->Prec *(VpBaseFig() + 1);

    GUARD_OBJ(d,VpCreateRbObject(mx, "0"));
    GUARD_OBJ(f,VpCreateRbObject(mx, "0"));

    VpActiveRound(d,c,VP_ROUND_DOWN,0);

    VpFrac(f, c);
    VpMult(rr,f,b);
    VpAddSub(ff,res,rr,1);

    *dv = d;
    *rv = ff;
    return (VALUE)0;
}
