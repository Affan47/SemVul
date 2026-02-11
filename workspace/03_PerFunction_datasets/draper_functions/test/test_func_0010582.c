do_qr_charsets(void)
{
	trace_ds("> QueryReply(CharacterSets)\n");
	space3270out(64);
#if defined(X3270_DBCS)
	if (dbcs)
		*obptr++ = 0x8e;
	else
#endif
		*obptr++ = 0x82;
	*obptr++ = 0x00;
	*obptr++ = SW_3279_2;
	*obptr++ = SH_3279_2;
	*obptr++ = 0x00;
	*obptr++ = 0x00;
	*obptr++ = 0x00;
	*obptr++ = 0x00;
#if defined(X3270_DBCS)
	if (dbcs)
		*obptr++ = 0x0b;
	else
#endif
		*obptr++ = 0x07;

	*obptr++ = 0x00;
#if defined(X3270_DBCS)
	if (dbcs)
		*obptr++ = 0x00;

	else
#endif
		*obptr++ = 0x10;


	*obptr++ = 0x00;
#if defined(X3270_DBCS)
	if (dbcs) {
		*obptr++ = 0x00;
		*obptr++ = 0x00;
		*obptr++ = 0x00;
		*obptr++ = 0x00;
	}
#endif
	SET32(obptr, cgcsgid);


	*obptr++ = 0x01;
	if (appres.apl_mode)
		*obptr++ = 0x00;

	else
		*obptr++ = 0x10;

	*obptr++ = 0xf1;
#if defined(X3270_DBCS)
	if (dbcs) {
		*obptr++ = 0x00;
		*obptr++ = 0x00;
		*obptr++ = 0x00;
		*obptr++ = 0x00;
	}
#endif
	*obptr++ = 0x03;
	*obptr++ = 0xc3;
	*obptr++ = 0x01;
	*obptr++ = 0x36;
#if defined(X3270_DBCS)
	if (dbcs) {
		*obptr++ = 0x80;
		*obptr++ = 0x20;
		*obptr++ = 0xf8;
		*obptr++ = SW_3279_2 * 2;
		*obptr++ = SH_3279_2;
		*obptr++ = 0x41;
		*obptr++ = 0x7f;
		SET32(obptr, cgcsgid_dbcs);
	}
#endif
}
