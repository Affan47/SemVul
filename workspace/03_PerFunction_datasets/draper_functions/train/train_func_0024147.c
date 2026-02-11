Math_ldexp(CTX ctx, ksfp_t *sfp _RIX)
{
	RETURNf_(ldexp(Float_to(double, sfp[1]), Int_to(int, sfp[2])));
}
