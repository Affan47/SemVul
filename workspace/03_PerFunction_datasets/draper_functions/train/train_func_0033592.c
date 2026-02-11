RemoveDirSend()
{
	LogMessage(Debug_Verbose, _T("CFtpControlSocket::RemoveDirSend()"));

	if (!m_pCurOpData)
	{
		LogMessage(__TFILE__, __LINE__, this, Debug_Info, _T("Empty m_pCurOpData"));
		ResetOperation(FZ_REPLY_INTERNALERROR);
		return FZ_REPLY_ERROR;
	}

	CFtpRemoveDirOpData *pData = static_cast<CFtpRemoveDirOpData *>(m_pCurOpData);

	CDirectoryCache cache;
	cache.InvalidateFile(*m_pCurrentServer, pData->path, pData->subDir);

	CServerPath path(CPathCache::Lookup(*m_pCurrentServer, pData->path, pData->subDir));
	if (path.IsEmpty())
	{
		path = pData->path;
		path.AddSegment(pData->subDir);
	}
	m_pEngine->InvalidateCurrentWorkingDirs(path);

	CPathCache::InvalidatePath(*m_pCurrentServer, pData->path, pData->subDir);

	if (pData->omitPath)
	{
		if (!Send(_T("RMD ") + pData->subDir))
			return FZ_REPLY_ERROR;
	}
	else
		if (!Send(_T("RMD ") + pData->fullPath.GetPath()))
			return FZ_REPLY_ERROR;

	return FZ_REPLY_WOULDBLOCK;
}
