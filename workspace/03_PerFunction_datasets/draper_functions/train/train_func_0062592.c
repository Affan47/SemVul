drmOpenByName(const char *name)
{
    int           i;
    int           fd;
    drmVersionPtr version;
    char *        id;


    for (i = 0; i < DRM_MAX_MINOR; i++) {
	if ((fd = drmOpenMinor(i, 1, DRM_NODE_RENDER)) >= 0) {
	    if ((version = drmGetVersion(fd))) {
		if (!strcmp(version->name, name)) {
		    drmFreeVersion(version);
		    id = drmGetBusid(fd);
		    drmMsg("drmGetBusid returned '%s'\n", id ? id : "NULL");
		    if (!id || !*id) {
			if (id)
			    drmFreeBusid(id);
			return fd;
		    } else {
			drmFreeBusid(id);
		    }
		} else {
		    drmFreeVersion(version);
		}
	    }
	    close(fd);
	}
    }

#ifdef __linux__

    for (i = 0; i < 8; i++) {
	char proc_name[64], buf[512];
	char *driver, *pt, *devstring;
	int  retcode;

	sprintf(proc_name, "/proc/dri/%d/name", i);
	if ((fd = open(proc_name, 0, 0)) >= 0) {
	    retcode = read(fd, buf, sizeof(buf)-1);
	    close(fd);
	    if (retcode) {
		buf[retcode-1] = '\0';
		for (driver = pt = buf; *pt && *pt != ' '; ++pt)
		    ;
		if (*pt) {
		    *pt = '\0';
		    if (!strcmp(driver, name)) {
			for (devstring = ++pt; *pt && *pt != ' '; ++pt)
			    ;
			if (*pt) {
			    return drmOpenByBusid(++pt);
			} else {
			    return drmOpenDevice(strtol(devstring, NULL, 0),i, DRM_NODE_RENDER);
			}
		    }
		}
	    }
	}
    }
#endif

    return -1;
}
