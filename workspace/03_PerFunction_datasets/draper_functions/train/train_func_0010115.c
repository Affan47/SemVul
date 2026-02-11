fcsExtractLockUser(
	NODE *			pTree,
	FLMBOOL			bExtractAsList,
	void *			pvLockUser)
{
	NODE *			pTmpNd;
	FLMUINT			uiItemCount = 0;
	FLMUINT			fieldPath[ 8];
	F_LOCK_USER *	pLockUser = NULL;
	FLMUINT			uiLoop;
	RCODE				rc = FERR_OK;

	if( !pTree)
	{
		if( bExtractAsList)
		{
			*((F_LOCK_USER **)pvLockUser) = NULL;
		}
		else
		{
			f_memset( (F_LOCK_USER *)pvLockUser, 0, sizeof( F_LOCK_USER));
		}
		goto Exit;
	}

	if( bExtractAsList)
	{
		pTmpNd = pTree;
		while( pTmpNd != NULL)
		{
			if( GedTagNum( pTmpNd) == FCS_LUSR_CONTEXT)
			{
				uiItemCount++;
			}
			pTmpNd = pTmpNd->next;
		}

		if( RC_BAD( rc = f_alloc(
			sizeof( F_LOCK_USER) * (uiItemCount + 1), &pLockUser)))
		{
			goto Exit;
		}

		*((F_LOCK_USER **)pvLockUser) = pLockUser;
	}
	else
	{
		pLockUser = (F_LOCK_USER *)pvLockUser;
		f_memset( pLockUser, 0, sizeof( F_LOCK_USER));
		uiItemCount = 1;
	}


	for( uiLoop = 0; uiLoop < uiItemCount; uiLoop++)
	{
		fieldPath[ 0] = FCS_LUSR_CONTEXT;
		fieldPath[ 1] = FCS_LUSR_THREAD_ID;
		fieldPath[ 2] = 0;

		if( (pTmpNd = GedPathFind( GED_TREE, pTree, fieldPath, 1)) != NULL)
		{
			(void) GedGetUINT( pTmpNd, &pLockUser[ uiLoop].uiThreadId);
		}

		fieldPath[ 0] = FCS_LUSR_CONTEXT;
		fieldPath[ 1] = FCS_LUSR_TIME;
		fieldPath[ 2] = 0;

		if( (pTmpNd = GedPathFind( GED_TREE, pTree, fieldPath, 1)) != NULL)
		{
			(void) GedGetUINT( pTmpNd, &pLockUser[ uiLoop].uiTime);
		}

		pTree = GedSibNext( pTree);
	}

	if( bExtractAsList)
	{
		f_memset( &(pLockUser[ uiItemCount]), 0, sizeof( F_LOCK_USER));
	}

Exit:

	return( rc);
}
