dumpFootprint(int where)
{
    register int fd;
    register char *base=config.log.dumpPrefix;
    register char *name;
    register int i;
    register fdInfoType *info;
    register connInfoType *conn;
    register FILE* f;

    if (!base) {
	syslog(LOG_ERR,"No dump file.");
	return;
    }

    name=malloc(strlen(base)+30);
    if (name==NULL) {
	freeSomeMemory(NULL);
	name=malloc(strlen(base)+30);
    }
    if (name==NULL) {
	syslog(LOG_ERR,"Out of memory in dumpFootprint");
	return;
    }
    sprintf(name,"%s.footprint.%d",base,negotInfo->pid);

    fd=open(name,O_WRONLY|O_CREAT|O_EXCL,0600);
    if (fd<0) {
	syslog(LOG_ERR,"Couldn't open %s for write",name);
	free(name);
	return;
    }
    f=fdopen(fd,"w");
    fprintf(f,"where=%d\n",where);

    i=fp_next ? fp_next-1 : fp_num-1;
    while (i!= fp_next) {
	if (fp[i].time)
	    fprintf(f,"%04x %4d 0x%08x 0x%08x %s",
		 fp[i].a, fp[i].b, fp[i].c, fp[i].d, ctime(&fp[i].time));
	i= i ? i-1 : fp_num-1;
    }

    fprintf(f,"\nfdInfo:\n");
    fprintf(f,"  addr     peer     conn      fd     flags    IPaddr  port\n");
    fprintf(f,"======== ======== ======== ======== ======== ======== =====\n");
    for (info=fdInfo; info<fdInfo+maxFd; info++) {
	fprintf(f,"%08x %08x %08x %8d %08x %08x %5d\n",
		info,info->peer,info->conn,info->fd,info->flags,
		ntohl(info->sin.sin_addr.s_addr),ntohs(info->sin.sin_port));
    }
    fprintf(f,"\nconnInfo:\n");
    fprintf(f,"  addr    client    udp     flags    error\n");
    fprintf(f,"======== ======== ======== ======== ========\n");
    for (conn=connInfo; conn<connInfo+config.daemon.maxClient; conn++) {
	fprintf(f,"%08x %08x %08x %8x %08x\n",
		conn,conn->client,conn->udp,conn->flags,conn->error);
    }

    fclose(f);
    free(name);
}
