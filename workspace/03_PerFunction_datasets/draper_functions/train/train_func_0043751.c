control_msg(int sock,void *dummy)
{
    CONTEXT context;
    SWC_MSG msg;
    USER_CALL *u_call;
    int len,i;

    len = un_recv(&context.un_ctx,s_control,&msg,sizeof(msg));
    if (len < 0) {
	diag(COMPONENT,DIAG_ERROR,"control_msg: un_recv: %s",strerror(errno));
	return;
    }
    if (len != sizeof(SWC_MSG))
	diag(COMPONENT,DIAG_FATAL,"control_msg: bad length (%d != %d)",len,
	  sizeof(SWC_MSG));
    switch (msg.type) {
	case smt_get:


	    i = msg.n;
	    for (u_call = calls; i && u_call; u_call = u_call->next) i--;
	    if (!u_call) {
		msg.n = -ENOENT;
		break;
	    }
	    msg.in = u_call->call.in.pvc;
	    msg.out = u_call->call.out.pvc;
	    msg.qos = u_call->call.out.qos;
	    break;
	case smt_add:
	    u_call = find_call(&msg.in,&msg.out);
	    if (u_call) {
		msg.n = -EEXIST;
		break;
	    }
	    u_call = alloc_t(USER_CALL);
	    memset(u_call,0,sizeof(USER_CALL));
	    u_call->call.in.pvc = msg.in;
	    u_call->call.out.pvc = msg.out;
	    fab_init(&u_call->call);
	    context.u_call = u_call;
	    fab_op(&u_call->call,RM_CLAIM(_RM_ANY) | RM_RSV(_RM_ANY),&msg.qos,
	      add_cb,&context);
	    return;
	case smt_del:
	    u_call = find_call(&msg.in,&msg.out);
	    if (!u_call) {
		msg.n = -ENOENT;
		break;
	    }
	    context.u_call = u_call;
	    fab_op(&u_call->call,RM_FREE,NULL,del_cb,&context);
	    return;
	default:
	    diag(COMPONENT,DIAG_FATAL,"control_msg: unknown message type %d",
	      msg.type);
    }
    if (un_send(&context.un_ctx,&msg,sizeof(msg)) < 0)
	diag(COMPONENT,DIAG_ERROR,"control_msg: un_send: %s",strerror(errno));
}
