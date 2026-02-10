getFieldVoid(
	FlmField *		pField)
{
	FLMUINT		uiSlot;

	if( !pField)
	{
		return( NULL);
	}

	if( !m_uiFldTblOffset ||
		pField > &(getFieldTable()[ m_uiFldTblOffset - 1]))
	{
		flmAssert( 0);
		return( NULL);
	}

	uiSlot = (pField - getFieldTable()) + 1;
	return( (void *)uiSlot);
}
