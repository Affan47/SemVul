find(
	void *		pvField,
	FLMUINT *	puiPathArray,
	FLMUINT		uiOccur,
	FLMUINT		uiFindOption)
{
	FlmField *	pSaveField;
	FLMUINT *	path;
	FLMUINT		uiLevel;
	FlmField *	pField = getFieldPointer( pvField);


	if( !pvField)
	{
		return( NULL);
	}

	if( !uiOccur)
	{
		uiOccur = 1;
	}

	uiLevel = getFieldLevel( pField);

	for(;;)
	{
		path = puiPathArray + ( getFieldLevel( pField) - uiLevel);
		pSaveField = pField;

		if( *path == pField->ui16FieldID)
		{
			if( *(path + 1) == 0 && (--uiOccur < 1))
			{
				return( getFieldVoid( pField));
			}

			if( (pField = firstChildField( pField)) != NULL)
			{
				continue;
			}
			pField = pSaveField;
		}

		do
		{
			pField = nextField( pField);
		}
		while( pField != NULL && getFieldLevel( pField) > getFieldLevel( pSaveField));

		if( !pField || getFieldLevel( pField) < uiLevel ||
			(uiFindOption != SEARCH_FOREST && getFieldLevel( pField) == uiLevel))
		{
			break;
		}
	}

	return( NULL);
}
