openLog(UINT32 type)
	{

		time_t currtime=0;
		switch(type)
			{
				case MSG_LOG:
#ifndef _WIN32
			openlog("AnonMix",0,LOG_USER);
#endif
				break;
				case MSG_FILE:
					if(pglobalOptions->getLogDir((UINT8*)m_strLogFile,1024)!=E_SUCCESS)
						return E_UNKNOWN;
					strcat(m_strLogFile,FILENAME_INFOLOG);
					if(pglobalOptions->getMaxLogFileSize()>0)
					{
						currtime=time(NULL);
						strftime(m_strLogFile+strlen(m_strLogFile),1024-strlen(m_strLogFile),"%Y%m%d-%H%M%S",localtime(&currtime));
						m_hFileInfo=open(m_strLogFile,O_APPEND|O_CREAT|O_WRONLY|O_NONBLOCK|O_LARGEFILE|O_SYNC,S_IREAD|S_IWRITE);
						setMaxLogFileSize(pglobalOptions->getMaxLogFileSize());
						m_NrOfWrites=0;
					}
					else
					{
						m_hFileInfo=open(m_strLogFile,O_APPEND|O_CREAT|O_WRONLY|O_NONBLOCK|O_LARGEFILE|O_SYNC,S_IREAD|S_IWRITE);
					}
				break;
#ifdef COMPRESSED_LOGS
				case MSG_COMPRESSED_FILE:
			char logdir[255];
			char buff[1024];
			if(pglobalOptions->getLogDir((UINT8*)logdir,255)!=E_SUCCESS)
				return E_UNKNOWN;
			strcpy(buff,logdir);
			strcat(buff,FILENAME_INFOLOG_GZ);
			tmpHandle=open(buff,O_APPEND|O_CREAT|O_WRONLY,S_IREAD|S_IWRITE);
			m_gzFileInfo=gzdopen(tmpHandle,"wb9");
			if(m_gzFileInfo==NULL)
				return E_UNKNOWN;
				break;
#endif
				default:
					return E_UNKNOWN;
		}
		return E_SUCCESS;
	}
