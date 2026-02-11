meta_parse_eopt(struct nlmsghdr *n, struct tcf_ematch_hdr *hdr,
			   struct bstr *args)
{
	int opnd;
	struct bstr *a;
	struct tcf_meta_hdr meta_hdr;
	unsigned long lvalue = 0, rvalue = 0;

	memset(&meta_hdr, 0, sizeof(meta_hdr));

	if (args == NULL)
		return PARSE_ERR(args, "meta: missing arguments");

	if (!bstrcmp(args, "list")) {
		list_meta_ids(stderr);
		return -1;
	}

	a = parse_object(args, args, &meta_hdr.left, &lvalue, NULL);
	if (a == PARSE_FAILURE)
		return -1;
	else if (a == NULL)
		return PARSE_ERR(args, "meta: missing operand");

	if (!bstrcmp(a, "eq"))
		opnd = TCF_EM_OPND_EQ;
	else if (!bstrcmp(a, "gt"))
		opnd = TCF_EM_OPND_GT;
	else if (!bstrcmp(a, "lt"))
		opnd = TCF_EM_OPND_LT;
	else
		return PARSE_ERR(a, "meta: invalid operand");

	meta_hdr.left.op = (__u8) opnd;

	if (a->next == NULL)
		return PARSE_ERR(args, "meta: missing rvalue");
	a = bstr_next(a);

	a = parse_object(args, a, &meta_hdr.right, &rvalue, &meta_hdr.left);
	if (a == PARSE_FAILURE)
		return -1;
	else if (a != NULL)
		return PARSE_ERR(a, "meta: unexpected trailer");


	addraw_l(n, MAX_MSG, hdr, sizeof(*hdr));

	addattr_l(n, MAX_MSG, TCA_EM_META_HDR, &meta_hdr, sizeof(meta_hdr));

	dump_value(n, TCA_EM_META_LVALUE, lvalue, &meta_hdr.left);
	dump_value(n, TCA_EM_META_RVALUE, rvalue, &meta_hdr.right);

	return 0;
}
