findListenInterfaces(void)
{
    struct ifconf		ifc;
    register struct ifreq	*ifreq;
    struct ifreq		myIfreq;
    char			buf[32768],*cplim;
    register int		i, fd=socket(AF_INET,SOCK_DGRAM,0);
    longLType			listenAddr;
    register void		*tmp;

    listenAddr.num=0;
    listenAddr.list=malloc(sizeof(*listenAddr.list));
    if (!listenAddr.list) {
nomem:	syslog(LOG_ERR,"Out of memory in findListenInterfaces");
	return listenAddr;
    }

    if (fd<0) {
	syslog(LOG_ERR,"socket failed in findListenInterfaces: %m");
	goto bailout;
    }

    ifc.ifc_len = sizeof buf;
    ifc.ifc_buf = buf;
    if (ioctl(fd,SIOCGIFCONF,&ifc)<0) {
	syslog(LOG_ERR,"SIOCGIFCONF failed: %m");
	goto bailout;
    }
    cplim=buf+ifc.ifc_len;
    for (i=0,ifreq=ifc.ifc_req;(char*)ifreq<cplim;i++,ifreq++) {
	memcpy(myIfreq.ifr_name,ifreq->ifr_name,sizeof(myIfreq.ifr_name));
	if (ioctl(fd,SIOCGIFFLAGS,&myIfreq)<0) {
	    syslog(LOG_WARNING,"SIOCGIFFLAGS failed on %s: %m",myIfreq.ifr_name);
	    continue;
	}
	if (myIfreq.ifr_flags&IFF_UP) {
	    register int j;
	    for (j=listenAddr.num-1;j>=0;j--) {
		if (listenAddr.list[j]==((struct sockaddr_in*)&ifreq->ifr_addr)->sin_addr.s_addr)
		    goto next_if;
	    }
	    tmp=realloc(listenAddr.list,(listenAddr.num+1)*sizeof(*listenAddr.list));
	    if (!tmp)
		goto nomem;
	    listenAddr.list=tmp;
	    listenAddr.list[listenAddr.num++]=((struct sockaddr_in*)&ifreq->ifr_addr)->sin_addr.s_addr;
	}
next_if: ;
    }
    close(fd);
bailout:
    if (!listenAddr.num)
	listenAddr.list[listenAddr.num++]=htonl(INADDR_ANY);

    return listenAddr;
}
