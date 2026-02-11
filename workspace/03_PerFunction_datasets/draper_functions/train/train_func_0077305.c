setUserID(DOMElement* elemGeneral)
{
	DOMElement* elemUID=NULL;
	UINT8 tmpBuff[TMP_BUFF_SIZE];
	UINT32 tmpLen = TMP_BUFF_SIZE;

	if(elemGeneral == NULL) return E_UNKNOWN;
	ASSERT_GENERAL_OPTIONS_PARENT
		(elemGeneral->getNodeName(), OPTIONS_NODE_USER_ID);


	getDOMChildByName(elemGeneral, OPTIONS_NODE_USER_ID, elemUID,false);

	if(getDOMElementValue(elemUID,tmpBuff,&tmpLen)==E_SUCCESS)
	{
		m_strUser=new char[tmpLen+1];
		memcpy(m_strUser,tmpBuff,tmpLen);
		m_strUser[tmpLen]=0;
	}
	return E_SUCCESS;
}
