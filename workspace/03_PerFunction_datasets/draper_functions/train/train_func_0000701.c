dumpClients(int sig)
{
    register int fd;
    register char *base=config.log.dumpPrefix;
    register char *name;
    register int i;
    register fdInfoType *info;

    now=time((time_t*)NULL);

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
	syslog(LOG_ERR,"Out of memory in dumpClients");
	return;
    }
    sprintf(name,"%s.client.%d",base,negotInfo->pid);

    unlink(name);
    fd=open(name,O_WRONLY|O_CREAT|O_EXCL,0600);
    if (fd<0) {
	syslog(LOG_ERR,"Couldn't open %s for write",name);
	free(name);
	return;
    }

    for (i=lowFd,info=fdInfo+lowFd; i<=highFd; i++,info++) {
	if ((info->flags&FD_IS_CLIENT) && !(info->flags&FD_IS_UDP) && info->fd>=0) {
	    register int ret;
	    register logRecType *rec;
	    rec=makeLogRec(info,0);
	    if (rec) do {
		ret=write(fd,rec,ntohs(rec->head.size));
	    } while (ret<0 && errno==EINTR);
	}
    }
    close(fd);
    free(name);
    if (debug&DBG_SANITY)
	dumpFootprint(-1);
}
