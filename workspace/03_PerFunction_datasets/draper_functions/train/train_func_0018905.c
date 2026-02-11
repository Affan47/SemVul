serviceThisCommand(DUL_NETWORKKEY ** network, DUL_ASSOCIATIONKEY ** association,
		   DUL_PRESENTATIONCONTEXT * ctx, MSG_TYPE messageType,
		   void **message, DUL_ASSOCIATESERVICEPARAMETERS * params)
{
    CONDITION
    cond;

    MSG_DumpMessage(message, stdout);
    switch (messageType) {
    case MSG_K_C_ECHO_REQ:
	appError("C-Echo");
	cond = 0;
	break;
    case MSG_K_C_STORE_REQ:
	appError("C-Store");
	cond = 0;
	break;
    case MSG_K_C_FIND_REQ:
	appError("C-Find");
	cond = 0;
	break;
    case MSG_K_C_MOVE_REQ:
	appError("C-Move");
	cond = 0;
	break;

    default:
	fprintf(stderr, "Unimplemented message type: %d\n", messageType);
	cond = 1;
	break;
    }
    return cond;
}
