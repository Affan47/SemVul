getStyleProperty(const char * szStyleName, const char * szPropertyName, const char *& szPropertyValue)
{
	PD_Style * pS;
	PD_Style ** ppS = &pS;
	if(!m_pPieceTable->getStyle(szStyleName, ppS))
		return false;

	return (*ppS)->getProperty(szPropertyName, szPropertyValue);
}
