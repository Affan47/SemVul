parse_unset(struct vcc *tl)
{
	const struct var *vp;

	vcc_NextToken(tl);
	ExpectErr(tl, ID);
	vp = vcc_FindVar(tl, tl->t, 1, "cannot be unset");
	ERRCHK(tl);
	assert(vp != NULL);
	if (vp->fmt != STRING || vp->http == NULL) {
		VSB_printf(tl->sb,
		    "Only http header variables can be unset.\n");
		vcc_ErrWhere(tl, tl->t);
		return;
	}
	ERRCHK(tl);
	Fb(tl, 1, "%s0);\n", vp->lname);
	vcc_NextToken(tl);
}
