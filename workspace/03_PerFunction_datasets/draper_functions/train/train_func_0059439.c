sendStatus(bool bIncludeCerts)
{
	if(!pglobalOptions->isFirstMix())
	{
		return E_SUCCESS;
	}


	if( !(m_pMix->isConnected()) && !bIncludeCerts )
	{
#ifdef DEBUG
		CAMsg::printMsg(LOG_INFO, "Mix not connected. Skipping status\n");
#endif
		return E_UNKNOWN;
	}

	UINT32 len;
	SINT32 ret;
	UINT8* strStatusXML=getStatusXMLAsString(bIncludeCerts,len);

	if(strStatusXML==NULL)
	{
		return E_UNKNOWN;
	}

	ret = sendHelo(strStatusXML, len, TCascadeStatus, (UINT8*)"Status Thread", REQUEST_COMMAND_STATUS);
	delete[] strStatusXML;
	strStatusXML = NULL;
	return ret;
}
