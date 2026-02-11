findLevelOneField(
	FLMUINT		uiFieldId,
	FLMBOOL		bFindInclusive,
	FLMUINT *	puiFieldPos)
{
	FIELD_ID *	pFieldId;
	void *		pvField = NULL;

	if (m_pucFieldIdTable)
	{
		if ((pFieldId = findFieldId( (FLMUINT16)uiFieldId, 0, puiFieldPos)) != NULL)
		{
			pvField = (void *)((FLMUINT)pFieldId->ui32FieldOffset);
		}
		else if (bFindInclusive &&
					*puiFieldPos < getFieldIdTableItemCount( m_pucFieldIdTable))
		{
			pFieldId = getFieldIdTable( m_pucFieldIdTable) + *puiFieldPos;
			pvField = (void *)((FLMUINT)pFieldId->ui32FieldOffset);
		}
	}
	else
	{
		flmAssert( m_uiFlags & RCA_FIELD_ID_TABLE_ENABLED);
	}
	return( pvField);
}
