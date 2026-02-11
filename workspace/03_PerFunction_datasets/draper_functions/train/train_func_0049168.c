sig_recv(SIGNALING_ENTITY *sig,
  int (*handler)(SIGNALING_ENTITY *sig,struct atmsvc_msg *msg))
{
    char buf[sizeof(struct atmsvc_msg)+1];
    int len;

    len = read(sig->s,buf,sizeof(buf));
    if (len == sizeof(struct atmsvc_msg))
	return handler(sig,(struct atmsvc_msg *) buf);
    if (len < 0)
	diag(COMPONENT,DIAG_ERROR,"read isp msg: %s",strerror(errno));
    else diag(COMPONENT,DIAG_ERROR,"bad isp msg: %d != %d",len,
	  sizeof(struct atmsvc_msg));
    return -1;
}
