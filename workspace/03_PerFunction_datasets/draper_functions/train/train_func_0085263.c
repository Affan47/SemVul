isakmp_sa_print(const struct isakmp_gen *ext,
		u_int item_len _U_,
		const u_char *ep, u_int32_t phase, u_int32_t doi0 _U_,
		u_int32_t proto0, int depth)
{
	const struct isakmp_pl_sa *p;
	struct isakmp_pl_sa sa;
	const u_int32_t *q;
	u_int32_t doi, sit, ident;
	const u_char *cp, *np;
	int t;

	printf("%s:", NPSTR(ISAKMP_NPTYPE_SA));

	p = (struct isakmp_pl_sa *)ext;
	TCHECK(*p);
	safememcpy(&sa, ext, sizeof(sa));
	doi = ntohl(sa.doi);
	sit = ntohl(sa.sit);
	if (doi != 1) {
		printf(" doi=%d", doi);
		printf(" situation=%u", (u_int32_t)ntohl(sa.sit));
		return (u_char *)(p + 1);
	}

	printf(" doi=ipsec");
	q = (u_int32_t *)&sa.sit;
	printf(" situation=");
	t = 0;
	if (sit & 0x01) {
		printf("identity");
		t++;
	}
	if (sit & 0x02) {
		printf("%ssecrecy", t ? "+" : "");
		t++;
	}
	if (sit & 0x04)
		printf("%sintegrity", t ? "+" : "");

	np = (u_char *)ext + sizeof(sa);
	if (sit != 0x01) {
		TCHECK2(*(ext + 1), sizeof(ident));
		safememcpy(&ident, ext + 1, sizeof(ident));
		printf(" ident=%u", (u_int32_t)ntohl(ident));
		np += sizeof(ident);
	}

	ext = (struct isakmp_gen *)np;
	TCHECK(*ext);

	cp = isakmp_sub_print(ISAKMP_NPTYPE_P, ext, ep, phase, doi, proto0,
		depth);

	return cp;
trunc:
	printf(" [|%s]", NPSTR(ISAKMP_NPTYPE_SA));
	return NULL;
}
