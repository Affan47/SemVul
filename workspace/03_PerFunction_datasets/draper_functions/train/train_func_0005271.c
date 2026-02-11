open_kernel(void)
{
    struct sockaddr_atmsvc addr;
    struct atm_qos qos;
    struct atm_sap sap;

    if ((kernel = socket(PF_ATMSVC,SOCK_DGRAM,0)) < 0)
	diag(COMPONENT,DIAG_FATAL,"socket: %s",strerror(errno));
    if (ioctl(kernel,ATMARPD_CTRL,0) < 0)
	diag(COMPONENT,DIAG_FATAL,"ioctl ATMARPD_CTRL: %s",strerror(errno));
    if ((incoming = socket(PF_ATMSVC,SOCK_DGRAM,0)) < 0)
	diag(COMPONENT,DIAG_FATAL,"socket: %s",strerror(errno));
    memset(&qos,0,sizeof(qos));
    qos.aal = ATM_AAL5;
    qos.rxtp.traffic_class = qos.txtp.traffic_class = ATM_ANYCLASS;
    if (setsockopt(incoming,SOL_ATM,SO_ATMQOS,&qos,sizeof(qos)) < 0)
	diag(COMPONENT,DIAG_FATAL,"setsockopt SO_ATMQOS: %s",strerror(errno));
    memset(&sap,0,sizeof(sap));
    sap.blli[0].l2_proto = ATM_L2_ISO8802;
    sap.blli[0].l3_proto = ATM_L3_NONE;
    if (setsockopt(incoming,SOL_ATM,SO_ATMSAP,&sap,sizeof(sap)) < 0)
	diag(COMPONENT,DIAG_FATAL,"setsockopt SO_ATMSAP: %s",strerror(errno));
    memset(&addr,0,sizeof(addr));
    addr.sas_family = AF_ATMSVC;
    if (bind(incoming,(struct sockaddr *) &addr,sizeof(addr)) >= 0) {
	if (listen(incoming,5) < 0)
	    diag(COMPONENT,DIAG_FATAL,"listen: %s",strerror(errno));
    }
    else {
	if (errno != EUNATCH)
	    diag(COMPONENT,DIAG_FATAL,"bind: %s",strerror(errno));
	diag(COMPONENT,DIAG_WARN,"SVCs are not available");
	(void) close(incoming);
	incoming = -1;
    }
    if ((inet = socket(PF_INET,SOCK_DGRAM,0)) < 0)
	diag(COMPONENT,DIAG_FATAL,"socket: %s",strerror(errno));
}
