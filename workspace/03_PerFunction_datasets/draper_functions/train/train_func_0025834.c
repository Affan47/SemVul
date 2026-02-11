BigCmpObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[])
{
	Tcl_Obj *result;
	mpz_ptr a, b;
	int cmp, res;
	char *cmd;

	if (objc != 3) {
		Tcl_WrongNumArgs(interp, 1, objv, "bignum bignum");
		return TCL_ERROR;
	}

	cmd = Tcl_GetStringFromObj(objv[0], NULL);
	if (Tcl_GetMpzFromObj(interp, objv[1], &a) != TCL_OK ||
	    Tcl_GetMpzFromObj(interp, objv[2], &b) != TCL_OK)
		return TCL_ERROR;
	cmp = mpz_cmp(a, b);

	result = Tcl_GetObjResult(interp);
	res = 0;
	switch(cmd[0]) {
	case '>':
		switch(cmd[1]) {
		case '=':
			if (cmp >= 0) res = 1;
			break;
		default:
			if (cmp > 0) res = 1;
			break;
		}
		break;
	case '<':
		switch(cmd[1]) {
		case '=':
			if (cmp <= 0) res = 1;
			break;
		default:
			if (cmp < 0) res = 1;
			break;
		}
		break;
	case '=':
		if (cmp == 0) res = 1;
		break;
	case '!':
		if (cmp != 0) res = 1;
		break;
	}
	Tcl_SetIntObj(result, res);
	return TCL_OK;
}
