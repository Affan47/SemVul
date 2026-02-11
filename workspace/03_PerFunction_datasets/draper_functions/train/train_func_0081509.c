vcc_Acl(struct vcc *tl)
{
	struct token *an;
	int i;
	char acln[1024];

	vcc_NextToken(tl);
	VTAILQ_INIT(&tl->acl);

	ExpectErr(tl, ID);
	an = tl->t;
	vcc_NextToken(tl);

	i = vcc_AddDef(tl, an, SYM_ACL);
	if (i > 1) {
		VSB_printf(tl->sb, "ACL %.*s redefined\n", PF(an));
		vcc_ErrWhere(tl, an);
		return;
	}
	bprintf(acln, "%.*s", PF(an));

	SkipToken(tl, '{');

	while (tl->t->tok != '}') {
		vcc_acl_entry(tl);
		ERRCHK(tl);
		SkipToken(tl, ';');
	}
	SkipToken(tl, '}');

	vcc_acl_emit(tl, acln, 0);
}
