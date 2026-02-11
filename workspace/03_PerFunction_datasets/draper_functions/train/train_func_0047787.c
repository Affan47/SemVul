flmIxFldPathSuitable(
	FLMUINT *	puiIxFldPath,
	FLMUINT *	puiQueryFldPath,
	FLMBOOL *	pbMustVerifyQueryPath
	)
{
	FLMBOOL	bIxPathHasWildcard = FALSE;
	FLMBOOL	bSuitable = FALSE;

	while (*puiIxFldPath)
	{
		if (*puiIxFldPath == FLM_ANY_FIELD)
		{


			if (*(puiIxFldPath + 1))
			{
				bIxPathHasWildcard = TRUE;
				if (*puiQueryFldPath == *(puiIxFldPath + 1))
				{


					puiIxFldPath += 2;
				}

				if (*puiQueryFldPath)
				{


					puiQueryFldPath++;
				}
				else
				{


					goto Exit;
				}
			}
			else
			{


				break;
			}
		}
		else if (*puiQueryFldPath != *puiIxFldPath)
		{


			goto Exit;
		}
		else
		{
			puiIxFldPath++;
			puiQueryFldPath++;
		}
	}

	bSuitable = TRUE;


	*pbMustVerifyQueryPath = (*puiQueryFldPath || bIxPathHasWildcard)
									 ? TRUE
									 : FALSE;
Exit:
	return( bSuitable);
}
