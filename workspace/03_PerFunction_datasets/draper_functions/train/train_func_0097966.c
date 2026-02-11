cs_diag_storemsg(CS_CONTEXT *context, CS_CLIENTMSG *message)
{
	struct cs_diag_msg **curptr;
	CS_INT msg_count = 0;

	tdsdump_log(TDS_DBG_FUNC, "cs_diag_storemsg(%p, %p)\n", context, message);

	curptr = &(context->msgstore);


	while (*curptr != NULL) {
		msg_count++;
		curptr = &((*curptr)->next);
	}


	if (context->cs_diag_msglimit != CS_NO_LIMIT &&
		msg_count >= context->cs_diag_msglimit) {
		return CS_FAIL;
	}

	*curptr = (struct cs_diag_msg *) malloc(sizeof(struct cs_diag_msg));
	if (*curptr == NULL) {
		return CS_FAIL;
	} else {
		(*curptr)->next = NULL;
		(*curptr)->msg  = malloc(sizeof(CS_CLIENTMSG));
		if ((*curptr)->msg == NULL) {
			return CS_FAIL;
		} else {
			memcpy((*curptr)->msg, message, sizeof(CS_CLIENTMSG));
		}
	}

	return CS_SUCCEED;
}
