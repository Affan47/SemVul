MainProcessing(void)
{
	unsigned int nCnt = mnFrameCnt;
	char szFileName[FILE_NAME_LEN];

	while(nCnt-- > 0)
	{
		CLEARx0(szFileName);
		MakeFileName("KDG", (mnFrameCnt-nCnt), szFileName);


		while(true)
		{
			fd_set stFd;
			struct timeval tv;
			int nRst;

			FD_ZERO(&stFd);
			FD_SET(mFdDevice, &stFd);

			tv.tv_sec = 2;
			tv.tv_usec = 2;

			nRst = select(mFdDevice + 1, &stFd, NULL, NULL, &tv);
			if(nRst == -1)
			{
				if(EINTR == errno) continue;
				fprintf(stderr, "Select Failure (%d)\n", errno);
				return;
			}

			if(nRst == 0)
			{
				fprintf(stderr, "Selec TimeOut \n");
				return;
			}
			if(ReadFrame()) break;
		}

		fprintf(stderr, " %d ",  mnFrameCnt-nCnt);
	}
	fprintf(stderr, "\n");
}
