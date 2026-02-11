log__enough_freespace(char  *path)
{

#ifdef _WIN32
DWORD	sectorsPerCluster, bytesPerSector, freeClusters, totalClusters;
char rootpath[4];
#else
#ifdef LINUX
	struct  statfs		buf;
#else
	struct	statvfs		buf;
#endif
#endif
	PRInt64			freeBytes;
	PRInt64 tmpval;


#ifdef _WIN32
    strncpy(rootpath, path, 3);
    rootpath[3] = '\0';

	if ( !GetDiskFreeSpace(rootpath, &sectorsPerCluster, &bytesPerSector,
				&freeClusters, &totalClusters)) {
		LDAPDebug(LDAP_DEBUG_ANY,
			  "log__enough_freespace: Unable to get the free space\n",0,0,0);
		return 1;
	} else {
	    LL_UI2L(freeBytes, freeClusters);
	    LL_UI2L(tmpval, sectorsPerCluster);
        LL_MUL(freeBytes, freeBytes, tmpval);
	    LL_UI2L(tmpval, bytesPerSector);
        LL_MUL(freeBytes, freeBytes, tmpval);


	}

#else
#ifdef LINUX
	if (statfs(path, &buf) == -1)
#else
	if (statvfs(path, &buf) == -1)
#endif
	{
		char buffer[BUFSIZ];
		PR_snprintf(buffer, sizeof(buffer),
			  		"log__enough_freespace: Unable to get the free space (errno:%d)\n",
					errno);
		log__error_emergency(buffer, 0, 1);
		return 1;
	} else {
	    LL_UI2L(freeBytes, buf.f_bavail);
	    LL_UI2L(tmpval, buf.f_bsize);
	    LL_MUL(freeBytes, freeBytes, tmpval);

	}
#endif
	LL_UI2L(tmpval, loginfo.log_access_minfreespace);
	if (LL_UCMP(freeBytes, <, tmpval)) {

	  return 0;
	}
	return 1;
}
