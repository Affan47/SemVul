store_other(pTHX_ stcxt_t *cxt, SV *sv)
{
	I32 len;
	char buf[80];

	TRACEME(("store_other"));


	if (
		cxt->forgive_me == 0 ||
		(cxt->forgive_me < 0 && !(cxt->forgive_me =
			SvTRUE(perl_get_sv("Storable::forgive_me", GV_ADD)) ? 1 : 0))
	)
		CROAK(("Can't store %s items", sv_reftype(sv, FALSE)));

	warn("Can't store item %s(0x%"UVxf")",
		sv_reftype(sv, FALSE), PTR2UV(sv));


	(void) sprintf(buf, "You lost %s(0x%"UVxf")%c", sv_reftype(sv, FALSE),
		       PTR2UV(sv), (char) 0);

	len = strlen(buf);
	STORE_SCALAR(buf, len);
	TRACEME(("ok (dummy \"%s\", length = %"IVdf")", buf, (IV) len));

	return 0;
}
