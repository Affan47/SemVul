exportRecord(
	HFDB			hDb,
	F_Pool *		pPool,
	NODE **		ppRoot)
{
	RCODE			rc = FERR_OK;
	FLMBYTE *	pucData;
	FLMBYTE *	pucEncData = NULL;
	FLMBYTE *	exPtr;
	FlmField *	pField = getFieldPointer(root());
	NODE *		pPrevNode = NULL;
	NODE *		pNode = NULL;
	FLMUINT		uiLevelBase = getFieldLevel( pField);
	FLMUINT		uiEncLength = 0;

	flmAssert( ppRoot != NULL);
	flmAssert( pPool != NULL);

	*ppRoot = NULL;

	while( pField)
	{
		if( *ppRoot)
		{
			if( (pNode = GedNodeMake( pPool,
				pField->ui16FieldID, &rc)) == NULL)
			{
				goto Exit;
			}
		}
		else
		{


			if( RC_BAD( rc = gedCreateSourceNode( pPool, pField->ui16FieldID,
				hDb, getContainerID(), getID(), &pNode)))
			{
				goto Exit;
			}
		}


		if( pPrevNode)
		{
			pPrevNode->next = pNode;
		}
		else
		{
			*ppRoot = pNode;
		}

		pNode->prior = pPrevNode;
		GedNodeLevelSet( pNode, (getFieldLevel( pField) - uiLevelBase));
		pPrevNode = pNode;

		if (isEncryptedField(pField))
		{
			uiEncLength = getEncryptedDataLength( pField);
			pucData = (FLMBYTE *)GedAllocSpace( pPool,
															pNode,
															getFieldDataType( pField),
															getFieldDataLength( pField),
															getEncryptionID( pField),
															uiEncLength);
			pucEncData = (FLMBYTE *)GedEncPtr( pNode);

			if( !pucData && uiEncLength)
			{
				rc = RC_SET( FERR_MEM);
				goto Exit;
			}
		}
		else
		{
			pucData = (FLMBYTE *)GedAllocSpace( pPool, pNode,
								getFieldDataType( pField), getFieldDataLength( pField));

			if( !pucData && getFieldDataLength( pField))
			{
				rc = RC_SET( FERR_MEM);
				goto Exit;
			}
		}


		if( getFieldDataLength( pField))
		{
			if( (exPtr = getDataPtr( pField)) == NULL)
			{
				rc = RC_SET( FERR_MEM);
				goto Exit;
			}
			f_memcpy( pucData, exPtr, getFieldDataLength( pField));
			if (pNode->ui32EncId)
			{
				flmAssert( pNode->ui32EncFlags & FLD_HAVE_DECRYPTED_DATA);
			}
		}

		if (pNode->ui32EncId)
		{
			if ((exPtr = getEncryptionDataPtr( pField)) == NULL)
			{
				rc = RC_SET( FERR_MEM);
				goto Exit;
			}

			flmAssert( uiEncLength);
			flmAssert( pNode->ui32EncFlags & FLD_HAVE_ENCRYPTED_DATA);
			f_memcpy( pucEncData, exPtr, uiEncLength);
		}


		if( isRightTruncated( pField))
		{
			GedSetRightTruncated( pNode);
		}

		if( isLeftTruncated( pField))
		{
			GedSetLeftTruncated( pNode);
		}

		pField = nextField( pField);
	}

Exit:

	return( rc);
}
