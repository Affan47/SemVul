fdictGetContainer(
	FDICT *		pDict,
	FLMUINT		uiContNum,
	LFILE **		ppLFile)
{
	ITT *			pItt;

	if( pDict && uiContNum < pDict->uiIttCnt && pDict->pIttTbl)
	{
		pItt = &pDict->pIttTbl[ uiContNum];


		if( !ITT_IS_CONTAINER( pItt))
		{
			return( RC_SET( FERR_BAD_CONTAINER));
		}
		if( ppLFile)
		{
			*ppLFile = (LFILE *) pItt->pvItem;
		}
	}
	else
	{


		if( uiContNum == FLM_DATA_CONTAINER)
		{
			if( ppLFile)
			{
				*ppLFile = &pDict->pLFileTbl[ LFILE_DATA_CONTAINER_OFFSET];
			}
		}
		else if( uiContNum == FLM_DICT_CONTAINER)
		{
			if( ppLFile)
			{
				*ppLFile = &pDict->pLFileTbl[ LFILE_DICT_CONTAINER_OFFSET];
			}
		}
		else if( uiContNum == FLM_TRACKER_CONTAINER)
		{
			if( ppLFile)
			{
				*ppLFile = &pDict->pLFileTbl[ LFILE_TRACKER_CONTAINER_OFFSET];
			}
		}
		else
		{
			return( RC_SET( FERR_BAD_CONTAINER));
		}
	}

	return( FERR_OK);
}
