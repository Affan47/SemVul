env_GetTimeout(interp, objc, objv, dbenv)
	Tcl_Interp *interp;
	int objc;
	Tcl_Obj *CONST objv[];
	DB_ENV *dbenv;
{
	static const struct {
		u_int32_t flag;
		char *arg;
	} timeout_flags[] = {
		{ DB_SET_LOCK_TIMEOUT, "lock" },
		{ DB_SET_REG_TIMEOUT, "reg" },
		{ DB_SET_TXN_TIMEOUT, "txn" },
		{ 0, NULL }
	};
	Tcl_Obj *res;
	db_timeout_t timeout;
	u_int32_t which;
	int i, ret, result;
	const char *arg;

	COMPQUIET(timeout, 0);

	if (objc != 3) {
		Tcl_WrongNumArgs(interp, 1, objv, NULL);
		return (TCL_ERROR);
	}

	arg = Tcl_GetStringFromObj(objv[2], NULL);
	which = 0;
	for (i = 0; timeout_flags[i].flag != 0; i++)
		if (strcmp(arg, timeout_flags[i].arg) == 0)
			which = timeout_flags[i].flag;
	if (which == 0) {
		ret = EINVAL;
		goto err;
	}

	ret = dbenv->get_timeout(dbenv, &timeout, which);
err:	if ((result = _ReturnSetup(interp, ret, DB_RETOK_STD(ret),
	    "env get_timeout")) == TCL_OK) {
		res = Tcl_NewLongObj((long)timeout);
		Tcl_SetObjResult(interp, res);
	}

	return (result);
}
