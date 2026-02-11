mobile_print(const u_char *bp, u_int length)
{
	const u_char *cp = bp +8 ;
	const struct mobile_ip *mob;
	struct cksum_vec vec[1];
	u_short proto,crc;
	u_char osp =0;

	mob = (const struct mobile_ip *)bp;

	if (length < MOBILE_SIZE || !TTEST(*mob)) {
		fputs("[|mobile]", stdout);
		return;
	}
	fputs("mobile: ", stdout);

	proto = EXTRACT_16BITS(&mob->proto);
	crc =  EXTRACT_16BITS(&mob->hcheck);
	if (proto & OSRC_PRES) {
		osp=1;
		cp +=4 ;
	}

	if (osp)  {
		fputs("[S] ",stdout);
		if (vflag)
			(void)printf("%s ",ipaddr_string(&mob->osrc));
	} else {
		fputs("[] ",stdout);
	}
	if (vflag) {
		(void)printf("> %s ",ipaddr_string(&mob->odst));
		(void)printf("(oproto=%d)",proto>>8);
	}
	vec[0].ptr = (const u_int8_t *)(void *)mob;
	vec[0].len = osp ? 12 : 8;
	if (in_cksum(vec, 1)!=0) {
		(void)printf(" (bad checksum %d)",crc);
	}

	return;
}
