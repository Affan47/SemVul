instw_makedirls(instw_t *instw) {
	int rcod=0;
	int status=0;
	struct stat translinfo;
	struct stat dirlsinfo;
	char wdirname[NAME_MAX+1];

#if DEBUG
	debug(2,"instw_makedirls(%p)\n",instw);
#endif


	if( !(instw->gstatus&INSTW_INITIALIZED) ||
	    !(instw->gstatus&INSTW_OKTRANSL)) {
	    strcpy(instw->mdirlspath,instw->path);
	    return 0;
	}


	if(instw_getstatus(instw,&status)) return -1;

	if( !(status&INSTW_TRANSLATED) ||
	    ((status&INSTW_TRANSLATED) && (status&INSTW_IDENTITY)) ) {
		strcpy(instw->mdirlspath,instw->path);
	} else {


		if(!(status & INSTW_ISINROOT)) {
			strcpy(instw->mdirlspath,instw->translpath);
		} else {
			rcod=true_stat(instw->translpath,&translinfo);

			sprintf(wdirname,"/%d_%lld_%lld",
					instw->pid,
					(long long int) translinfo.st_dev,
					(long long int) translinfo.st_ino);

			strcpy(instw->mdirlspath,instw->mdirls);
			strcat(instw->mdirlspath,wdirname);


			if(!true_stat(instw->mdirlspath,&dirlsinfo)) {
				unlink_recursive(instw->mdirlspath);
			}
			true_mkdir(instw->mdirlspath,S_IRWXU);


			instw_filldirls(instw);
		}
	}

#if DEBUG
	instw_print(instw);
#endif

	return rcod;
}
