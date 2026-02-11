multi_xfer_send_file(PSNET_SOCKET_RELIABLE who, char *filename, int cfile_flags, int flags)
{
	xfer_entry temp_entry;
	int handle;


	if(Multi_xfer_locked){
		return -1;
	}


	handle = multi_xfer_get_free_handle();
	if(handle == -1){
		return -1;
	}


	memset(&temp_entry,0,sizeof(xfer_entry));


	strcpy_s(temp_entry.filename,filename);


	temp_entry.file = NULL;
	temp_entry.file = cfopen(filename,"rb",CFILE_NORMAL,cfile_flags);
	if(temp_entry.file == NULL){
#ifdef MULTI_XFER_VERBOSE
		nprintf(("Network","MULTI XFER : Could not open file %s on xfer send!\n",filename));
#endif

		return -1;
	}


	temp_entry.file_size = -1;
	temp_entry.file_size = cfilelength(temp_entry.file);
	if(temp_entry.file_size == -1){
#ifdef MULTI_XFER_VERBOSE
		nprintf(("Network","MULTI XFER : Could not get file length for file %s on xfer send\n",filename));
#endif
		return -1;
	}
	temp_entry.file_ptr = 0;


	if(!cf_chksum_short(temp_entry.file,&temp_entry.file_chksum)){
#ifdef MULTI_XFER_VERBOSE
		nprintf(("Network","MULTI XFER : Could not get file checksum for file %s on xfer send\n",filename));
#endif
		return -1;
	}
#ifdef MULTI_XFER_VERBOSE
	nprintf(("Network","MULTI XFER : Got file %s checksum of %d\n",temp_entry.filename,(int)temp_entry.file_chksum));
#endif

	cfseek(temp_entry.file,0,CF_SEEK_SET);


	temp_entry.flags |= (MULTI_XFER_FLAG_USED | MULTI_XFER_FLAG_SEND | MULTI_XFER_FLAG_PENDING);
	temp_entry.flags |= flags;


	temp_entry.file_socket = who;


	temp_entry.sig = multi_xfer_get_sig();


	memset(&Multi_xfer_entry[handle],0,sizeof(xfer_entry));
	memcpy(&Multi_xfer_entry[handle],&temp_entry,sizeof(xfer_entry));

	return handle;
}
