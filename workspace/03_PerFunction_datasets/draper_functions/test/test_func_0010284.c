del_cb(CALL *call,int cause,void *more,void *user)
{
    CONTEXT *context = user;
    SWC_MSG msg;
    USER_CALL **walk;

    memset(&msg,0,sizeof(msg));
    msg.type = smt_del;
    msg.n = cause ? -EIO : 0;
    if (!cause) {
	for (walk = &calls; *walk && *walk != context->u_call;
	  walk = &(*walk)->next);
	if (!*walk)
	    diag(COMPONENT,DIAG_FATAL,"del_cb: call %p not found",
	      context->u_call);
	*walk = (*walk)->next;
	free(context->u_call);
    }
    if (un_send(&context->un_ctx,&msg,sizeof(msg)) < 0)
	diag(COMPONENT,DIAG_ERROR,"control_msg: un_send: %s",strerror(errno));
}
