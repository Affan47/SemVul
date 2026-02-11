retrieve_netint(pTHX_ stcxt_t *cxt, const char *cname)
{
	SV *sv;
	I32 iv;

	TRACEME(("retrieve_netint (#%d)", cxt->tagnum));

	READ_I32(iv);
#ifdef HAS_NTOHL
	sv = newSViv((int) ntohl(iv));
	TRACEME(("network integer %d", (int) ntohl(iv)));
#else
	sv = newSViv(iv);
	TRACEME(("network integer (as-is) %d", iv));
#endif
	SEEN(sv, cname, 0);

	TRACEME(("ok (retrieve_netint at 0x%"UVxf")", PTR2UV(sv)));

	return sv;
}
