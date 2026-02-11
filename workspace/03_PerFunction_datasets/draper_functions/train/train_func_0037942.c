parseInfoServices(DOMElement* a_infoServiceNode)
{
	DOMElement* elemAllowReconfig;
	getDOMChildByName(a_infoServiceNode, OPTIONS_NODE_ALLOW_AUTO_CONF, elemAllowReconfig, false);
	DOMNodeList* isList = getElementsByTagName(a_infoServiceNode, OPTIONS_NODE_INFOSERVICE);

	if(isList->getLength() == 0)
	{
		return E_SUCCESS;
	}


	if(m_addrInfoServices!=NULL)
	{
		for(UINT32 i=0;i<m_addrInfoServicesSize;i++)
		{
			delete m_addrInfoServices[i];
			m_addrInfoServices[i] = NULL;
		}
		delete[] m_addrInfoServices;
	}
	m_addrInfoServicesSize=0;
	m_addrInfoServices=NULL;

	UINT32 nrListenerInterfaces;
	m_addrInfoServicesSize = 0;
	m_addrInfoServices = new CAListenerInterface*[isList->getLength()];
	CAListenerInterface** isListenerInterfaces;
	for (UINT32 i = 0; i < isList->getLength(); i++)
	{

		DOMElement* elemListenerInterfaces;
		getDOMChildByName(isList->item(i),CAListenerInterface::XML_ELEMENT_CONTAINER_NAME,elemListenerInterfaces,false);
		isListenerInterfaces = CAListenerInterface::getInstance(elemListenerInterfaces, nrListenerInterfaces);
		if (nrListenerInterfaces > 0)
		{

			m_addrInfoServices[m_addrInfoServicesSize] = isListenerInterfaces[0];
			m_addrInfoServicesSize++;
			for (UINT32 j = 1; j < nrListenerInterfaces; j++)
			{

				delete isListenerInterfaces[j];
				isListenerInterfaces[j] = NULL;
			}
		}
	}
	UINT8 tmpBuff[255];
	UINT32 tmpLen=255;
	if(getDOMElementValue(elemAllowReconfig,tmpBuff,&tmpLen)==E_SUCCESS)
	{
		m_bAcceptReconfiguration = (strcmp("True",(char*)tmpBuff) == 0);
	}

	return E_SUCCESS;
}
