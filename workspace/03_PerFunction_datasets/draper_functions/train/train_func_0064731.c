Perl_init_dbargs(pTHX)
{
    AV *const args = PL_dbargs = GvAV(gv_AVadd((gv_fetchpvs("DB::args",
							    GV_ADDMULTI,
							    SVt_PVAV))));

    if (AvREAL(args)) {


	av_clear(args);
	if (SvTIED_mg((const SV *)args, PERL_MAGIC_tied))
	    Perl_croak(aTHX_ "Cannot set tied @DB::args");
    }
    AvREIFY_only(PL_dbargs);
}
