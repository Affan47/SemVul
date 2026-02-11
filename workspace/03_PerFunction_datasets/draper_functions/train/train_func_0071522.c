rfc1035_mkquery(struct rfc1035_res *res,
			unsigned opcode,
			const struct rfc1035_query *questions,
			unsigned nquestions,
			void (*func)(const char *, unsigned, void *), void *arg)
{
struct {
	unsigned char idhi, idlo;
	unsigned char infohi, infolo;
	unsigned char qhi, qlo;
	unsigned char ahi, alo;
	unsigned char nhi, nlo;
	unsigned char auhi, aulo;
	} header;
unsigned cnt;

	unsigned id=rfc1035_next_randid(res);

	header.idhi= id >> 8;
	header.idlo= id;

	header.infohi= (opcode << 3) & 0x78;

	if (!res->norecursive)
		header.infohi |= 1;
	header.infolo=0;
	header.qhi=nquestions >> 8;
	header.qlo=nquestions;
	header.ahi=0;
	header.alo=0;
	header.nhi=0;
	header.nlo=0;
	header.auhi=0;
	header.aulo=0;

	if (res->dnssec_payload_size)
		header.aulo=1;

	(*func)( (const char *)&header, sizeof(header), arg);
	cnt=sizeof(header);
	if (nquestions)
		if (mkpacketq(func, arg, &cnt, questions, nquestions,
			questions->name, 0, res))	return (-1);

	if (res->dnssec_payload_size)
	{


		struct {
			char opt_root_domain_name;
			char opt_type_hi;
			char opt_type_lo;
			char opt_class_hi;
			char opt_class_lo;
			char opt_extendedrcode;
			char opt_version;
			char opt_ttl_zhi;
			char opt_ttl_zlo;
			char opt_rdlen_hi;
			char opt_rdlen_lo;
		} rfc2671_43;

		memset(&rfc2671_43, 0, sizeof(rfc2671_43));

		rfc2671_43.opt_type_lo=RFC1035_TYPE_OPT;

		rfc2671_43.opt_class_hi= res->dnssec_payload_size >> 8;
		rfc2671_43.opt_class_lo= res->dnssec_payload_size;
		rfc2671_43.opt_ttl_zhi |= 0x80;

		(*func)((char *)&rfc2671_43, sizeof(rfc2671_43), arg);
	}

	return (0);
}
