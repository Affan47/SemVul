StartUpload( CString dstfile, ulonglong length, ulonglong pos, ulonglong chunksize, CString srcfile, bool uget, bool adcget, CString adcTTH, bool compress )
{
	if ( srcfile.IsEmpty() && (eMedium == eltFILE) )
	{
		DPRINTF("CTransfer::StartUpload: source file empty\n");
		return -1;
	}

	if ( m_bIdle == false )
	{
		DPRINTF("ctransfer: other transfer is running\n");
		return -1;
	}

	if ( eMode == estTRANSFERDOWNLOAD )
	{
		DPRINTF("ctransfer: wrong transfer mode\n");
		return -1;
	}

	TransferMutex.Lock();
	eMode            = estTRANSFERUPLOAD;
	m_nStartPosition = pos;
	m_nEndPosition   = length;
	m_nFileSize      = length;
	sDstFilename     = dstfile;
	sSrcFilename     = srcfile;
	m_sTTH           = adcTTH;
	TransferMutex.UnLock();

	m_nTransfered = 0;

	if ( chunksize == 0 )
		m_nChunkSize = length-pos;
	else
		m_nChunkSize = chunksize;
	m_nPendingSendBytes = 0;


	InitTime();

	if ( compress )
	{
		m_nDataType = 2;
	}
	else
	{
		m_nDataType = 0;
	}

	if ( adcget )
	{
		if ( GetMedium() == eltTTHL )
		{
			SendADCSnd( eAdcTTHL, adcTTH, pos, m_nChunkSize, compress );
		}
		else if ( GetMedium() == eltLIST )
		{
			SendADCSnd( eAdcList, CString(), pos, m_nChunkSize, compress, dstfile );
		}
		else if ( GetMedium() == eltBUFFER )
		{
			SendADCSnd( eAdcFile, CString(), pos, m_nChunkSize, compress, dstfile );
		}
		else if ( adcTTH.IsEmpty() )
		{
			SendADCSnd( eAdcFile, CString(), pos, m_nChunkSize, compress, "/" + dstfile );
		}
		else
		{
			SendADCSnd( eAdcFile, adcTTH, pos, m_nChunkSize, compress );
		}

		if ( (eMode != estTRANSFERUPLOAD) || (m_bIdle == false) )
		{
			DPRINTF("Warning: not in uploadmode/idle ADCSND [%d/%d]\n",eMode,m_bIdle);
		}
		else
		{
			DoInitUpload();
		}
	}
	else if ( uget || compress )
	{
		SendSending(m_nChunkSize);


		if ( (eMode != estTRANSFERUPLOAD) || (m_bIdle == false) )
		{
			DPRINTF("Warning: not in uploadmode/idle SEND [%d/%d]\n",eMode,m_bIdle);
		}
		else
		{
			DoInitUpload();
		}
	}
	else
	{

		SendFileLength(length);
	}

	return 0;
}
