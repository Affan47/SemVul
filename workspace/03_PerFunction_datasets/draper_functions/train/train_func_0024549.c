createFieldIdTable(
	FLMBOOL	bTruncateTable)
{
	RCODE		rc = FERR_OK;
	void *	pvField;

	if (!(m_uiFlags & RCA_FIELD_ID_TABLE_ENABLED))
	{
		m_uiFlags |= RCA_FIELD_ID_TABLE_ENABLED;
		pvField = firstChild( root());
		while (pvField)
		{
			if (RC_BAD( rc = addToFieldIdTable( (FLMUINT16)getFieldID( pvField),
										(FIELDLINK)((FLMUINT)pvField))))
			{
				goto Exit;
			}
			pvField = nextSibling( pvField);
		}
	}
	if (m_uiFlags & RCA_NEED_TO_SORT_FIELD_ID_TABLE)
	{
		sortFieldIdTable();
	}
	if (bTruncateTable)
	{
		if (RC_BAD( rc = truncateFieldIdTable()))
		{
			goto Exit;
		}
	}

Exit:

	return( rc);
}
