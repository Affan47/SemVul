MkdirParseResponse(bool successful, const wxString& reply)
{
	LogMessage(Debug_Verbose, _T("CSftpControlSocket::MkdirParseResonse"));

	if (!m_pCurOpData)
	{
		LogMessage(__TFILE__, __LINE__, this, Debug_Info, _T("Empty m_pCurOpData"));
		ResetOperation(FZ_REPLY_INTERNALERROR);
		return FZ_REPLY_ERROR;
	}

	CMkdirOpData *pData = static_cast<CMkdirOpData *>(m_pCurOpData);
	LogMessage(Debug_Debug, _T("  state = %d"), pData->opState);

	bool error = false;
	switch (pData->opState)
	{
	case mkd_findparent:
		if (successful)
		{
			m_CurrentPath = pData->currentPath;
			pData->opState = mkd_mkdsub;
		}
		else if (pData->currentPath == pData->commonParent)
			pData->opState = mkd_tryfull;
		else if (pData->currentPath.HasParent())
		{
			pData->segments.push_front(pData->currentPath.GetLastSegment());
			pData->currentPath = pData->currentPath.GetParent();
		}
		else
			pData->opState = mkd_tryfull;
		break;
	case mkd_mkdsub:
		if (successful)
		{
			if (pData->segments.empty())
			{
				LogMessage(__TFILE__, __LINE__, this, Debug_Warning, _T("  pData->segments is empty"));
				ResetOperation(FZ_REPLY_INTERNALERROR);
				return FZ_REPLY_ERROR;
			}
			CDirectoryCache cache;
			cache.UpdateFile(*m_pCurrentServer, pData->currentPath, pData->segments.front(), true, CDirectoryCache::dir);
			m_pEngine->SendDirectoryListingNotification(pData->currentPath, false, true, false);

			pData->currentPath.AddSegment(pData->segments.front());
			pData->segments.pop_front();

			if (pData->segments.empty())
			{
				ResetOperation(FZ_REPLY_OK);
				return FZ_REPLY_OK;
			}
			else
				pData->opState = mkd_cwdsub;
		}
		else
			pData->opState = mkd_tryfull;
		break;
	case mkd_cwdsub:
		if (successful)
		{
			m_CurrentPath = pData->currentPath;
			pData->opState = mkd_mkdsub;
		}
		else
			pData->opState = mkd_tryfull;
		break;
	case mkd_tryfull:
		if (!successful)
			error = true;
		else
		{
			ResetOperation(FZ_REPLY_OK);
			return FZ_REPLY_OK;
		}
		break;
	default:
		LogMessage(__TFILE__, __LINE__, this, Debug_Warning, _T("unknown op state: %d"), pData->opState);
		ResetOperation(FZ_REPLY_INTERNALERROR);
		return FZ_REPLY_ERROR;
	}

	if (error)
	{
		ResetOperation(FZ_REPLY_ERROR);
		return FZ_REPLY_ERROR;
	}

	return MkdirSend();
}
