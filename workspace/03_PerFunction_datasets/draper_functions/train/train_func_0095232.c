dbrpcparam(DBPROCESS * dbproc, const char paramname[], BYTE status, int type, DBINT maxlen, DBINT datalen, BYTE * value)
{
	char *name = NULL;
	DBREMOTE_PROC *rpc;
	DBREMOTE_PROC_PARAM **pparam;
	DBREMOTE_PROC_PARAM *param;

	tdsdump_log(TDS_DBG_FUNC, "dbrpcparam(%p, %s, 0x%x, %d, %d, %d, %p)\n",
				   dbproc, paramname, status, type, maxlen, datalen, value);
	CHECK_DBPROC();
	DBPERROR_RETURN(IS_TDSDEAD(dbproc->tds_socket), SYBEDDNE);
	CHECK_PARAMETER(dbproc->rpc, SYBERPCS, FAIL);


	if (is_fixed_type(type)) {
		if (datalen != 0)
			datalen = -1;
	} else {


		DBPERROR_RETURN(datalen < 0, SYBERPIL);
	}


	DBPERROR_RETURN(value == NULL && datalen != 0, SYBERPNULL);


	DBPERROR_RETURN(is_nullable_type(type) && datalen < 0, SYBERPUL);


	if (status & DBRPCRETURN) {
		if (is_fixed_type(type)) {
			maxlen = -1;
		} else {
			if (maxlen == -1)
				maxlen = 255;
		}
	} else {


		DBPERROR_RETURN3(maxlen != -1 && maxlen != 0, SYBEIPV, (int) maxlen, "maxlen", "dbrpcparam");
		maxlen = -1;
	}


	param = (DBREMOTE_PROC_PARAM *) malloc(sizeof(DBREMOTE_PROC_PARAM));
	if (param == NULL) {
		dbperror(dbproc, SYBEMEM, 0);
		return FAIL;
	}

	if (paramname) {
		name = strdup(paramname);
		if (name == NULL) {
			free(param);
			dbperror(dbproc, SYBEMEM, 0);
			return FAIL;
		}
	}


	param->next = NULL;
	param->name = name;
	param->status = status;
	param->type = type;
	param->maxlen = maxlen;
	param->datalen = datalen;


	if (datalen == 0)
		param->value = NULL;
	else
		param->value = value;


	for (rpc = dbproc->rpc; rpc->next != NULL; rpc = rpc->next)
		;
	for (pparam = &rpc->param_list; *pparam != NULL; pparam = &(*pparam)->next);


	*pparam = param;

	tdsdump_log(TDS_DBG_INFO1, "dbrpcparam() added parameter \"%s\"\n", (paramname) ? paramname : "");

	return SUCCEED;
}
