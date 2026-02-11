printFieldPulldown(
	F_NameTable *	pNameTable,
	FLMUINT			uiSelectedField
	)
{
	FLMUINT			uiNextPos;
	char				szNameBuf[ 128];
	FLMUINT			uiId;
	FLMUINT			uiType;

	fnPrintf( m_pHRequest, "<select name=\"fieldlist\">\n");

	if( !pNameTable)
	{
		goto Exit;
	}

	uiNextPos = 0;
	while( pNameTable->getNextTagNameOrder( &uiNextPos, NULL,
		szNameBuf, sizeof( szNameBuf), &uiId, &uiType))
	{
		if( uiType != FLM_FIELD_TAG)
		{
			continue;
		}

		printSelectOption( uiSelectedField, uiId, (char *)szNameBuf);
	}

Exit:

	fnPrintf( m_pHRequest, "</select>\n");
}
