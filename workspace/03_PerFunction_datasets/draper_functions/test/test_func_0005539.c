vcc_Acl_Hack(struct vcc *tl, char *b)
{
	char acln[32];
	unsigned tcond;

	VTAILQ_INIT(&tl->acl);
	tcond = tl->t->tok;
	vcc_NextToken(tl);
	bprintf(acln, "%u", tl->cnt);
	vcc_acl_entry(tl);
	vcc_acl_emit(tl, acln, 1);
	sprintf(b, "%smatch_acl_anon_%s(sp, \v1)",
	    (tcond == T_NEQ ? "!" : ""), acln);
}
