parent(
	FlmField *		pField)
{
	FLMUINT		uiLevel;

	if( !pField)
	{
		return( NULL);
	}

	uiLevel = getFieldLevel( pField);
	while( (pField = prevField( pField)) != NULL &&
		getFieldLevel( pField) >= uiLevel)
	{
		;
	}

#ifdef FLM_DEBUG
	if( pField)
	{
		flmAssert( pField->ui16FieldID);
	}
#endif

	return( getFieldVoid( pField));
}
