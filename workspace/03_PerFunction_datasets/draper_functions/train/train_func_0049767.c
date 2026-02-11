sendNameTable(
	FLMUINT			uiTag,
	F_NameTable *	pNameTable)
{
	void *			pvMark = m_pPool->poolMark();
	NODE *			pRootNd;
	NODE *			pNd;
	NODE *			pItemIdNd;
	FLMUINT			uiMaxNameChars = 1024;
	FLMUNICODE *	puzItemName = NULL;
	FLMUINT			uiId;
	FLMUINT			uiType;
	FLMUINT			uiSubType;
	FLMUINT			uiNextPos;
	RCODE				rc = FERR_OK;


	if( !pNameTable)
	{
		rc = RC_SET( FERR_MEM);
		goto Exit;
	}


	if( RC_BAD( rc = m_pPool->poolAlloc( uiMaxNameChars * sizeof( FLMUNICODE),
		(void **)&puzItemName)))
	{
		goto Exit;
	}


	switch( uiTag)
	{
		case WIRE_VALUE_NAME_TABLE:
		{
			uiTag |= WIRE_VALUE_TYPE_HTD <<
				WIRE_VALUE_TYPE_START_BIT;

			if( RC_BAD( rc = m_pDOStream->writeUShort( (FLMUINT16)uiTag)))
			{
				goto Exit;
			}


			if( (pRootNd = GedNodeMake( m_pPool,
				FCS_NAME_TABLE_CONTEXT, &rc)) == NULL)
			{
				goto Exit;
			}

			uiNextPos = 0;
			while( pNameTable->getNextTagNumOrder( &uiNextPos, puzItemName,
				NULL, uiMaxNameChars * sizeof( FLMUNICODE),
				&uiId, &uiType, &uiSubType))
			{
				if( (pItemIdNd = GedNodeMake( m_pPool,
					FCS_NAME_TABLE_ITEM_ID, &rc)) == NULL)
				{
					goto Exit;
				}

				if( RC_BAD( rc = GedPutUINT( m_pPool, pItemIdNd, uiId)))
				{
					goto Exit;
				}

				if( (pNd = GedNodeMake( m_pPool,
					FCS_NAME_TABLE_ITEM_NAME, &rc)) == NULL)
				{
					goto Exit;
				}

				if( RC_BAD( rc = GedPutUNICODE( m_pPool, pNd, puzItemName)))
				{
					goto Exit;
				}

				GedChildGraft( pItemIdNd, pNd, GED_LAST);

				if( (pNd = GedNodeMake( m_pPool,
					FCS_NAME_TABLE_ITEM_TYPE, &rc)) == NULL)
				{
					goto Exit;
				}

				if( RC_BAD( rc = GedPutUINT( m_pPool, pNd, uiType)))
				{
					goto Exit;
				}

				GedChildGraft( pItemIdNd, pNd, GED_LAST);

				if( (pNd = GedNodeMake( m_pPool,
					FCS_NAME_TABLE_ITEM_SUBTYPE, &rc)) == NULL)
				{
					goto Exit;
				}

				if( RC_BAD( rc = GedPutUINT( m_pPool, pNd, uiSubType)))
				{
					goto Exit;
				}

				GedChildGraft( pItemIdNd, pNd, GED_LAST);


				GedChildGraft( pRootNd, pItemIdNd, GED_LAST);


				f_yieldCPU();
			}


			if( RC_BAD( rc = m_pDOStream->writeHTD( pRootNd,
				NULL, TRUE, m_bSendGedcom)))
			{
				goto Exit;
			}
			break;
		}

		default:
		{
#ifdef FLM_DEBUG
			flmAssert( 0);
#else
			rc = RC_SET( FERR_NOT_IMPLEMENTED);
			goto Exit;
#endif
		}
	}

Exit:

	m_pPool->poolReset( pvMark);
	return( rc);
}
