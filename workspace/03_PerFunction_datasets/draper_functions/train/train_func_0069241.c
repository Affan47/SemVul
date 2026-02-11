send_status(SIG_ENTITY *sig,SOCKET *sock,unsigned long call_ref,
  unsigned char cause,...)
{
    va_list ap;
    Q_DSC dsc;
    int size;

    q_create(&dsc,q_buffer,MAX_Q_MSG);
    q_assign(&dsc,QF_msg_type,ATM_MSG_STATUS);
    if (sock) {
	q_assign(&dsc,QF_call_ref,sock->call_ref);
	q_assign(&dsc,QF_call_state,(int) sock->call_state);
	if (sock->ep_ref >= 0) {
	    q_assign(&dsc,QF_ep_ref,sock->ep_ref);
	    q_assign(&dsc,QF_ep_state,eps_map[sock->call_state]);
	}
    }
    else {
	q_assign(&dsc,QF_call_ref,call_ref);
	q_assign(&dsc,QF_call_state,0);
    }
    q_assign(&dsc,QF_cause,cause);
    va_start(ap,cause);
    switch (cause) {
	case ATM_CV_UNKNOWN_MSG_TYPE:
	case ATM_CV_INCOMP_MSG:
	    q_assign(&dsc,QF_bad_msg_type,va_arg(ap,unsigned int));
	    break;
	case ATM_CV_MAND_IE_MISSING:
	case ATM_CV_INVALID_IE:
	    {
		unsigned char ie;

		ie = va_arg(ap,unsigned int);
		q_write(&dsc,QF_ie_id6,&ie,1);
		break;
	    }
	default:
	    ;
    }
    va_end(ap);
    if ((size = q_close(&dsc)) >= 0) to_signaling(sig,q_buffer,size);
}
