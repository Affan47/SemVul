flmFieldIterate(
	FDB *				pDb,
	F_Pool *			pPool,
	QTYPES			eFldType,
	FQNODE *			pOpCB,
	FlmRecord *		pRecord,
	FLMBOOL			bHaveKey,
	FLMBOOL			bGetAtomVals,
	FLMUINT			uiAction,
	FQATOM *			pResult)
{
	RCODE				rc = FERR_OK;
	FlmRecord *		pFieldRec = NULL;
	void *			pField = NULL;
	FLMBOOL			bSavedInvisTrans;

	if (bHaveKey)
	{


		pResult->eType = FLM_UNKNOWN;
	}
	else
	{
		CB_ENTER( pDb, &bSavedInvisTrans);
		rc = pOpCB->pQAtom->val.QueryFld.fnGetField(
			pOpCB->pQAtom->val.QueryFld.pvUserData, pRecord, (HFDB) pDb,
			pOpCB->pQAtom->val.QueryFld.puiFldPath, uiAction,
			&pFieldRec, &pField, NULL);
		CB_EXIT( pDb, bSavedInvisTrans);

		if (RC_BAD( rc))
		{
			goto Exit;
		}

		if (!pField)
		{
			if (!bGetAtomVals)
			{
				pResult->eType = FLM_BOOL_VAL;
				pResult->val.uiBool = FLM_FALSE;
			}
			else
			{
				if ((pOpCB->pQAtom->uiFlags & FLM_USE_DEFAULT_VALUE) &&
					 (uiAction == FLM_FLD_FIRST))
				{
					if (RC_BAD( rc = flmCurGetAtomVal( pFieldRec, NULL, pPool,
								  eFldType, pResult)))
					{
						goto Exit;
					}
				}
				else
				{
					pResult->eType = FLM_UNKNOWN;
				}
			}
		}
		else
		{
			if (!bGetAtomVals)
			{
				pResult->eType = FLM_BOOL_VAL;
				pResult->val.uiBool = FLM_TRUE;
			}
			else if (RC_BAD( rc = flmCurGetAtomVal( pFieldRec, pField, pPool,
								 eFldType, pResult)))
			{
				goto Exit;
			}
		}
	}

Exit:

	return (rc);
}
