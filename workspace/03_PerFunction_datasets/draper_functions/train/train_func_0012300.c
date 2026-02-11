get_addr(int itf,LOCAL_ADDR *local_addr)
{
    struct atmif_sioc req;
    struct sockaddr_atmsvc buffer[MAX_LOCAL_ADDRS];
    LOCAL_ADDR *from,*to;
    int addrs,i;

    for (from = to = local_addr; from->state != ls_unused; from++)
	if (from->state != ls_removed) {
	    from->state = ls_removed;
	    *to++ = *from;
	}
    to->state = ls_unused;
    req.number = itf;
    req.arg = buffer;
    req.length = sizeof(buffer);
    if (ioctl(entities->signaling,ATM_GETADDR,&req) < 0)
	diag(COMPONENT,DIAG_FATAL,"ioctl ATM_GETADDR yields \"%s\"",
	  strerror(errno));
    addrs = req.length/sizeof(struct sockaddr_atmsvc);
    for (i = 0; i < addrs; i++) {
	for (from = local_addr; from->state != ls_unused; from++)
	    if (atm_equal((struct sockaddr *) (buffer+i),
	      (struct sockaddr *) &from->addr,0,0)) break;
	if (from->state != ls_unused) from->state = ls_same;
	else if (to == local_addr+MAX_LOCAL_ADDRS-1)
		diag(COMPONENT,DIAG_WARN,"local address table overflow");
	    else {
		to->state = ls_added;
		to->addr = buffer[i];
		to++;
		to->state = ls_unused;
	    }
    }
    return addrs;
}
