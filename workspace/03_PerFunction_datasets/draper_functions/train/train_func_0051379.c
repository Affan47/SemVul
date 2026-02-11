ssl_callback_TmpRSA(SSL *pSSL, int nExport, int nKeyLen)
{
	if (nExport && (nKeyLen == 512))
		return tmprsakey512;
	else if (nExport && (nKeyLen == 1024))
		return tmprsakey1024;
	else
		return tmprsakey1024;
}
