flmIncrField(
	FlmRecord *		pRecord,
	FLMUINT			uiTagNum)
{
	RCODE				rc = FERR_OK;
	void *			pvField;

	if( (pvField = pRecord->find( pRecord->root(), uiTagNum, 1)) != NULL)
	{
		FLMUINT		uiNum;

		if( RC_OK( rc = pRecord->getUINT( pvField, &uiNum)))
		{
			uiNum++;
			rc = pRecord->setUINT( pvField, uiNum);
		}
	}
	else
	{


		if( RC_OK( rc = pRecord->insertLast( 1, uiTagNum,
			FLM_NUMBER_TYPE, &pvField)))
		{
			rc = pRecord->setUINT( pvField, 1);
		}
	}

	return( rc);
}
