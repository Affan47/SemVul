tcl_DbAssociate(interp, objc, objv, dbp)
	Tcl_Interp *interp;
	int objc;
	Tcl_Obj *CONST objv[];
	DB *dbp;
{
	static const char *dbaopts[] = {
		"-create",
		"-immutable_key",
		"-txn",
		NULL
	};
	enum dbaopts {
		DBA_CREATE,
		DBA_IMMUTABLE_KEY,
		DBA_TXN
	};
	DB *sdbp;
	DB_TXN *txn;
	DBTCL_INFO *sdbip;
	int i, optindex, result, ret;
	char *arg, msg[MSG_SIZE];
	u_int32_t flag;

	txn = NULL;
	result = TCL_OK;
	flag = 0;
	if (objc < 2) {
		Tcl_WrongNumArgs(interp, 2, objv, "[callback] secondary");
		return (TCL_ERROR);
	}

	i = 2;
	while (i < objc) {
		if (Tcl_GetIndexFromObj(interp, objv[i], dbaopts, "option",
		    TCL_EXACT, &optindex) != TCL_OK) {
			result = IS_HELP(objv[i]);
			if (result == TCL_OK)
				return (result);
			result = TCL_OK;
			Tcl_ResetResult(interp);
			break;
		}
		i++;
		switch ((enum dbaopts)optindex) {
		case DBA_CREATE:
			flag |= DB_CREATE;
			break;
		case DBA_IMMUTABLE_KEY:
			flag |= DB_IMMUTABLE_KEY;
			break;
		case DBA_TXN:
			if (i > (objc - 1)) {
				Tcl_WrongNumArgs(interp, 2, objv, "?-txn id?");
				result = TCL_ERROR;
				break;
			}
			arg = Tcl_GetStringFromObj(objv[i++], NULL);
			txn = NAME_TO_TXN(arg);
			if (txn == NULL) {
				snprintf(msg, MSG_SIZE,
				    "Associate: Invalid txn: %s\n", arg);
				Tcl_SetResult(interp, msg, TCL_VOLATILE);
				result = TCL_ERROR;
			}
			break;
		}
	}
	if (result != TCL_OK)
		return (result);


	arg = Tcl_GetStringFromObj(objv[objc - 1], NULL);
	sdbp = NAME_TO_DB(arg);
	if (sdbp == NULL) {
		snprintf(msg, MSG_SIZE,
		    "Associate: Invalid database handle: %s\n", arg);
		Tcl_SetResult(interp, msg, TCL_VOLATILE);
		return (TCL_ERROR);
	}


	sdbip = (DBTCL_INFO *)sdbp->api_internal;

#ifdef CONFIG_TEST
	if (i != objc - 1) {
#else
	if (i != objc - 1) {
#endif


		sdbip->i_second_call = objv[objc - 2];
		Tcl_IncrRefCount(sdbip->i_second_call);


		_debug_check();

		ret = dbp->associate(dbp,
		    txn, sdbp, tcl_second_call, flag);
	} else {


		sdbip->i_second_call = NULL;
		ret = dbp->associate(dbp, txn, sdbp, NULL, flag);
	}
	result = _ReturnSetup(interp, ret, DB_RETOK_STD(ret), "associate");

	return (result);
}
