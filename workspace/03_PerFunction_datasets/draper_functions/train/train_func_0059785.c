complete_connect(VCC *vcc)
{
    struct sockaddr_atmsvc dummy;

    if (!vcc->connecting)
	diag(COMPONENT,DIAG_FATAL,"connecting non-connecting VCC 0x%p",vcc);
    memset(&dummy,0,sizeof(dummy));
    if (!connect(vcc->fd,(struct sockaddr *) &dummy,sizeof(dummy))) {
	if (ioctl(vcc->fd,ATMARP_MKIP,CLIP_DEFAULT_IDLETIMER) < 0) {
	    diag(COMPONENT,DIAG_ERROR,"ioctl ATMARP_MKIP: %s",strerror(errno));
	    (void) do_close(vcc->fd);
	    vcc_failed(vcc);
	}
	vcc_connected(vcc);
    }
    else {
	diag(COMPONENT,DIAG_INFO,"[2]connect: %s",strerror(errno));
	(void) do_close(vcc->fd);
	vcc_failed(vcc);
    }
}
