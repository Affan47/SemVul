RemoveQueueFile( CString nick, CString hubname, CString remotefile )
{
	bool res = false;
	DCTransferFileObject * TransferFileObject = 0;
	DCTransferQueueObject * TransferObject = 0;

	if ( (TransferObject = m_pDownloadQueue->GetUserTransferObject( nick, hubname, CString() )) != 0 )
	{
		if ( remotefile.NotEmpty() )
		{
			if ( (TransferFileObject = m_pDownloadQueue->GetUserFileObject( nick, hubname, CString(), remotefile )) != 0 )
			{
				if ( TransferFileObject->m_eState != etfsTRANSFER )
				{
					res = true;
				}
				else
				{
					DPRINTF("WARNING: RemoveQueueFile: file transfer is running\n");
				}
			}
		}
		else
		{
			if ( TransferObject->eState != etwsRUN )
			{
				res = true;
			}
			else
			{
				DPRINTF("WARNING: RemoveQueueFile: transfer is running\n");
			}
		}

		if ( res )
		{
			SendFileInfo( TransferObject, TransferFileObject, true );
			res = m_pDownloadQueue->DelUserFileObject( nick, hubname, CString(), remotefile );
		}
	}

	return res;
}
