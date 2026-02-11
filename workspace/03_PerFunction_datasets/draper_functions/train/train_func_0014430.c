connect_vcc(struct sockaddr *remote,const struct atm_qos *qos,int sndbuf,
  int timeout)
{
    int fd,error,flags;

    if (remote->sa_family == AF_ATMSVC && incoming < 0) return -EUNATCH;
    if ((fd = socket(remote->sa_family,SOCK_DGRAM,0)) < 0) {
	error = -errno;
	diag(COMPONENT,DIAG_ERROR,"socket: %s",strerror(errno));
	return error;
    }
    if (setsockopt(fd,SOL_ATM,SO_ATMQOS,qos,sizeof(*qos)) < 0) {
	error = -errno;
	diag(COMPONENT,DIAG_ERROR,"setsockopt SO_ATMQOS: %s",strerror(errno));
	return error;
    }
    if (sndbuf)
	if (setsockopt(fd,SOL_SOCKET,SO_SNDBUF,&sndbuf,sizeof(sndbuf)) < 0) {
	    error = -errno;
	    diag(COMPONENT,DIAG_ERROR,"setsockopt SO_SNDBUF: %s",
	      strerror(errno));
	    return error;
	}
    if ((flags = fcntl(fd,F_GETFL)) < 0) {
	error = -errno;
	diag(COMPONENT,DIAG_ERROR,"fcntl F_GETFL: %s",strerror(errno));
	return error;
    }
    flags |= O_NONBLOCK;
    if (fcntl(fd,F_SETFL,flags) < 0) {
	error = -errno;
	diag(COMPONENT,DIAG_ERROR,"fcntl F_GETFL: %s",strerror(errno));
	return error;
    }
    if (remote->sa_family == AF_ATMSVC) {
	struct atm_sap sap;

	memset(&sap,0,sizeof(sap));
	sap.blli[0].l2_proto = ATM_L2_ISO8802;
	sap.blli[0].l3_proto = ATM_L3_NONE;
	if (setsockopt(fd,SOL_ATM,SO_ATMSAP,&sap,sizeof(sap)) < 0) {
	    error = -errno;
	    diag(COMPONENT,DIAG_ERROR,"setsockopt SO_ATMSAP: %s",
	      strerror(errno));
	    return error;
	}
    }

    if (connect(fd,remote,remote->sa_family == AF_ATMPVC ?
      sizeof(struct sockaddr_atmpvc) : sizeof(struct sockaddr_atmsvc)) < 0) {
	if (errno != EINPROGRESS) {
	    error = -errno;
	    diag(COMPONENT,DIAG_ERROR,"[1]connect: %s",strerror(errno));
	    return error;
	}
	return fd;
    }
    if (ioctl(fd,ATMARP_MKIP,timeout) < 0) {
	error = -errno;
        diag(COMPONENT,DIAG_ERROR,"ioctl ATMARP_MKIP: %s",strerror(errno));
        (void) do_close(fd);
        return error;
    }
    return fd;
}
