pkg_uncache(
        pTHX_
	HV *cache,
	HV *pkg,
	const char *method)
{
	const char *hvname = HvNAME_get(pkg);
	PERL_UNUSED_ARG(method);
	(void) hv_delete(cache, hvname, strlen(hvname), G_DISCARD);
}
