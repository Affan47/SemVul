vcc_dir_dns_parse_list(struct vcc *tl, int *serial)
{
	unsigned char a[4],mask;
	int ret;
	ERRCHK(tl);
	SkipToken(tl, '{');
	if (tl->t->tok != CSTR) {
		vcc_dir_dns_parse_backend_options(tl);
		ERRCHK(tl);
	}

	while (tl->t->tok == CSTR) {
		mask = 32;
		ret = sscanf(tl->t->dec, "%hhu.%hhu.%hhu.%hhu",
		    &a[0], &a[1], &a[2], &a[3]);
		if (ret != 4) {
			VSB_printf(tl->sb, "Incomplete IP supplied: ");
			vcc_ErrToken(tl, tl->t);
			VSB_printf(tl->sb, " at\n");
			vcc_ErrWhere(tl, tl->t);
			ERRCHK(tl);
		}

		vcc_NextToken(tl);
		if (tl->t->tok == '/') {
			vcc_NextToken(tl);
			mask = vcc_UintVal(tl);
			ERRCHK(tl);
		}
		vcc_dir_dns_makebackend(tl,serial,a,mask);
		SkipToken(tl,';');
	}
	ExpectErr(tl, '}');
}
