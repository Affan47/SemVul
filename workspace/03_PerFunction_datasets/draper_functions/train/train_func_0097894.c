S_assert_uft8_cache_coherent(pTHX_ const char *const func, STRLEN from_cache,
			     STRLEN real, SV *const sv)
{
    PERL_ARGS_ASSERT_ASSERT_UFT8_CACHE_COHERENT;


    if (from_cache == real)
	return;


    SAVEI8(PL_utf8cache);
    PL_utf8cache = 0;
    Perl_croak(aTHX_ "panic: %s cache %"UVuf" real %"UVuf" for %"SVf,
	       func, (UV) from_cache, (UV) real, SVfARG(sv));
}
