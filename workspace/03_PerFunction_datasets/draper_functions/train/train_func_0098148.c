VarParseShort(VarParser *vp, Boolean *freeResult)
{
	char	vname[2];
	Var	*v;
	char	*value;

	vname[0] = vp->ptr[0];
	vname[1] = '\0';

	vp->ptr++;

	v = VarFindAny(vname, vp->ctxt);
	if (v != NULL) {
		value = VarExpand(v, vp);
		*freeResult = TRUE;
		return (value);
	}


	if ((vp->ctxt == VAR_CMD) || (vp->ctxt == VAR_GLOBAL)) {


		switch (vname[0]) {
		case '@':
			*freeResult = TRUE;
			return (estrdup("$(.TARGET)"));
		case '%':
			*freeResult = TRUE;
			return (estrdup("$(.ARCHIVE)"));
		case '*':
			*freeResult = TRUE;
			return (estrdup("$(.PREFIX)"));
		case '!':
			*freeResult = TRUE;
			return (estrdup("$(.MEMBER)"));
		default:
			*freeResult = FALSE;
			return (vp->err ? var_Error : varNoError);
		}
	}


	*freeResult = FALSE;
	return (vp->err ? var_Error : varNoError);
}
