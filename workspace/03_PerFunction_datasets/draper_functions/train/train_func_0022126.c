removePidFile()
	{
		if(pglobalOptions==NULL)
			{
				return;
			}
		UINT8 strPidFile[512];
		if(pglobalOptions->getPidFile(strPidFile,512)==E_SUCCESS)
			{
				if(::remove((char*)strPidFile)!=0)
					{
#ifndef _WIN32
						int old_uid=geteuid();
						seteuid(0);
						::remove((char*)strPidFile);
						seteuid(old_uid);
#endif
					}
			}
	}
