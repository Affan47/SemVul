FileTransfer(const wxString localFile, const CServerPath &remotePath,
									const wxString &remoteFile, bool download,
									const CFileTransferCommand::t_transferSettings& transferSettings)
{
	LogMessage(Debug_Verbose, _T("CFtpControlSocket::FileTransfer()"));

	if (localFile == _T(""))
	{
		if (!download)
			ResetOperation(FZ_REPLY_CRITICALERROR | FZ_REPLY_NOTSUPPORTED);
		else
			ResetOperation(FZ_REPLY_SYNTAXERROR);
		return FZ_REPLY_ERROR;
	}

	if (download)
	{
		wxString filename = remotePath.FormatFilename(remoteFile);
		LogMessage(Status, _("Starting download of %s"), filename.c_str());
	}
	else
	{
		LogMessage(Status, _("Starting upload of %s"), localFile.c_str());
	}
	if (m_pCurOpData)
	{
		LogMessage(__TFILE__, __LINE__, this, Debug_Info, _T("deleting nonzero pData"));
		delete m_pCurOpData;
	}

	CFtpFileTransferOpData *pData = new CFtpFileTransferOpData(download, localFile, remoteFile, remotePath);
	m_pCurOpData = pData;

	pData->transferSettings = transferSettings;
	pData->binary = transferSettings.binary;

	wxLongLong size;
	bool isLink;
	if (CLocalFileSystem::GetFileInfo(pData->localFile, isLink, &size, 0, 0) == CLocalFileSystem::file)
		pData->localFileSize = size.GetValue();

	pData->opState = filetransfer_waitcwd;

	if (pData->remotePath.GetType() == DEFAULT)
		pData->remotePath.SetType(m_pCurrentServer->GetType());

	int res = ChangeDir(pData->remotePath);
	if (res != FZ_REPLY_OK)
		return res;

	return ParseSubcommandResult(FZ_REPLY_OK);
}
