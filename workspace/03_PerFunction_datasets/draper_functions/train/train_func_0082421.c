getPublicKeyAsXML(UINT8* buff,UINT32 *len)
	{
		if(m_pRSA==NULL||buff==NULL)
			return E_UNKNOWN;
		XERCES_CPP_NAMESPACE::DOMDocument* pDoc=createDOMDocument();
		DOMElement* elemRoot=NULL;
		getPublicKeyAsDOMElement(elemRoot,pDoc);
		DOM_Output::dumpToMem(elemRoot,buff,len);
		if (pDoc != NULL)
		{
			pDoc->release();
			pDoc = NULL;
		}
		return E_SUCCESS;
	}
