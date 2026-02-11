flmModField(
	FlmRecord *		pRecord,
	FLMUINT			uiTagNum,
	const void *	pvData,
	FLMUINT			uiDataLen,
	FLMUINT			uiDataType)
{
	RCODE				rc = FERR_OK;
	void *			pvField;

	if( (pvField = pRecord->find( pRecord->root(), uiTagNum)) == NULL)
	{


		if( RC_BAD( rc = pRecord->insertLast( 1, uiTagNum, uiDataType, &pvField)))
		{
			goto Exit;
		}
	}

	switch( uiDataType)
	{
		case FLM_TEXT_TYPE:
		{
			rc = pRecord->setNative( pvField, (const char *)pvData);
			break;
		}

		case FLM_NUMBER_TYPE:
		{
			FLMUINT	uiNum;
			switch (uiDataLen)
			{
				case 0:
					uiNum = (FLMUINT)(*((FLMUINT *)(pvData)));
					rc = pRecord->setUINT( pvField, uiNum);
					break;
				case 1:
					uiNum = (FLMUINT)(*((FLMBYTE *)(pvData)));
					rc = pRecord->setUINT( pvField, uiNum);
					break;
				case 2:
					uiNum = (FLMUINT)(*((FLMUINT16 *)(pvData)));
					rc = pRecord->setUINT( pvField, uiNum);
					break;
				case 4:
					uiNum = (FLMUINT)(*((FLMUINT32 *)(pvData)));
					rc = pRecord->setUINT( pvField, uiNum);
					break;
				case 8:
					rc = pRecord->setUINT64( pvField, *((FLMUINT64 *)(pvData)));
					break;
				default:
					flmAssert( 0);
					rc = RC_SET( FERR_INVALID_PARM);
					goto Exit;
			}
			break;
		}

		case FLM_BINARY_TYPE:
		{
			rc = pRecord->setBinary( pvField, pvData, uiDataLen);
			break;
		}

		default :
		{
			flmAssert( 0);
			break;
		}
	}

Exit:

	return( rc);
}
