getLastField( void)
{
	FLMUINT		uiLoop;
	FlmField *	pField = NULL;

	if( !m_uiFldTblOffset)
	{
		goto Exit;
	}

	for( uiLoop = m_uiFldTblOffset; uiLoop; uiLoop--)
	{
		pField = &(getFieldTable()[ uiLoop - 1]);

		if( pField->ui16FieldID)
		{
			break;
		}
	}

Exit:

	return( pField);
}
