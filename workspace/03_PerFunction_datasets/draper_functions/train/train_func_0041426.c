CreateFileDownloadErrMsg(char* reason, unsigned int reasonLen)
{
	FileTransferMsg fileDownloadErrMsg;
	int length = sz_rfbFileDownloadFailedMsg + reasonLen + 1;
	rfbFileDownloadFailedMsg *pFDF = NULL;
	char *pFollow = NULL;

	char *pData = (char*) calloc(length, sizeof(char));
	memset(&fileDownloadErrMsg, 0, sizeof(FileTransferMsg));
	if(pData == NULL) {
		rfbLog("File [%s]: Method [%s]: pData is NULL\n",
				__FILE__, __FUNCTION__);
		return fileDownloadErrMsg;
	}

	pFDF = (rfbFileDownloadFailedMsg *) pData;
	pFollow = &pData[sz_rfbFileDownloadFailedMsg];

	pFDF->type = rfbFileDownloadFailed;
	pFDF->reasonLen = Swap16IfLE(reasonLen);
	memcpy(pFollow, reason, reasonLen);

	fileDownloadErrMsg.data	= pData;
	fileDownloadErrMsg.length	= length;

	return fileDownloadErrMsg;
}
