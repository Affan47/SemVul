printBlobField(
	FlmRecord *	pRec,
	void *		pvField,
	FLMUINT		uiFieldCounter,
	FLMBOOL		bReadOnly)
{
	RCODE			rc = FERR_OK;
	FlmBlob *	pBlob = NULL;
	char			szPath[F_PATH_MAX_SIZE];
	FLMUINT		uiLen;

	if (RC_BAD( rc = pRec->getBlob( pvField, &pBlob)))
	{
		fnPrintf( m_pHRequest,
					"** Failed to retrieve Blob object (Return Code = 0x%04X, %s) **",
					(unsigned long) rc, FlmErrorString( rc));
		goto Exit;
	}

	uiLen = ((FlmBlobImp *) pBlob)->getDataLength();
	if (uiLen == 0)
	{
		if (!bReadOnly)
		{
			fnPrintf( m_pHRequest,
						"<input class=\"fieldclass\" name=\"field%d\" type=\"text\" "
						"value=\"\" size=\"%d\">", uiFieldCounter,
						MAX_FIELD_SIZE( 0));
		}

		goto Exit;
	}

	if (RC_BAD( rc = pBlob->buildFileName( szPath)))
	{
		fnPrintf( m_pHRequest,
					"** Failed to retrieve Blob filename (Return Code = 0x%04X, %s) **",
					(unsigned) rc, FlmErrorString( rc));
		goto Exit;
	}

	if (bReadOnly)
	{
		fnPrintf( m_pHRequest, "<font color=\"0db3ae\">");
		printEncodedString( szPath, HTML_ENCODING);
		fnPrintf( m_pHRequest, "</font>");
	}
	else
	{
		fnPrintf( m_pHRequest,
					"<input class=\"fieldclass\" name=\"field%d\" type=\"text\" value=\"",
				uiFieldCounter);
		printEncodedString( szPath, HTML_ENCODING);
		fnPrintf( m_pHRequest, "\" size=\"20\">");
	}

Exit:

	if (pBlob)
	{
		pBlob->Release();
	}
}
