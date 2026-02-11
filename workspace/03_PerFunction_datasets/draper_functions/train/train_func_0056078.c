positionToOrAfter(
	FDB *				pDb,
	FLMUINT *		puiRecordId)
{
	RCODE				rc;
	FLMUINT			uiRecordId = *puiRecordId;
	RECSET *			pSaveRecSet = m_pCurSet;
	FLMUINT			uiSaveRecId = m_curRecPos.uiRecordId;

	if( RC_BAD( rc = checkTransaction( pDb)))
	{
		goto Exit;
	}


	for( m_pCurSet = m_pFirstSet; m_pCurSet; m_pCurSet = m_pCurSet->pNext)
	{
		if( m_pCurSet->fromKey.uiRecordId <= uiRecordId
		 && m_pCurSet->untilKey.uiRecordId >= uiRecordId)
		{
			break;
		}
	}
	if (!m_pCurSet)
	{
		rc = RC_SET( FERR_EOF_HIT);
		goto Exit;
	}

	m_curRecPos.uiRecordId = uiRecordId;
	if( RC_BAD( rc = setRecPosition( pDb, TRUE, &m_curRecPos, &m_curRecPos)))
	{

		goto Exit;
	}
	*puiRecordId = m_curRecPos.uiRecordId;

Exit:
	if (RC_BAD( rc))
	{
		m_pCurSet = pSaveRecSet;
		m_curRecPos.uiRecordId = uiSaveRecId;
	}
	return( rc);
}
