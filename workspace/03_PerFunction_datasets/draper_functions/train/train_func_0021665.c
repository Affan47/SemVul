DUL_MakePresentationCtx(DUL_PRESENTATIONCONTEXT ** ctx,
		     DUL_SC_ROLE proposedSCRole, DUL_SC_ROLE acceptedSCRole,
		      DUL_PRESENTATIONCONTEXTID ctxID, unsigned char result,
			const char *abstractSyntax, const char *transferSyntax,...)
{
    va_list
	args;
    LST_HEAD
	* lst;
    DUL_TRANSFERSYNTAX
	* transfer;

    *ctx = (DUL_PRESENTATIONCONTEXT *) malloc(sizeof(**ctx));
    if (*ctx == NULL) return EC_MemoryExhausted;

    (void) memset(*ctx, 0, sizeof(**ctx));
    lst = LST_Create();
    if (lst == NULL) return EC_MemoryExhausted;

    (*ctx)->presentationContextID = ctxID;
    (*ctx)->result = result;
    (*ctx)->proposedSCRole = proposedSCRole;
    (*ctx)->acceptedSCRole = acceptedSCRole;
    strcpy((*ctx)->abstractSyntax, abstractSyntax);

    va_start(args, transferSyntax);
    strcpy((*ctx)->acceptedTransferSyntax, transferSyntax);
    while ((transferSyntax = va_arg(args, char *)) != NULL)
    {
	if (strlen(transferSyntax) != 0)
	{
	    transfer = (DUL_TRANSFERSYNTAX*)malloc(sizeof(DUL_TRANSFERSYNTAX));
	    if (transfer == NULL) return EC_MemoryExhausted;
	    strcpy(transfer->transferSyntax, transferSyntax);
	    OFCondition cond = LST_Enqueue(&lst, (LST_NODE*)transfer);
	    if (cond.bad()) return cond;
	}
    }
    va_end(args);
    (*ctx)->proposedTransferSyntax = lst;
    return EC_Normal;
}
