setListenerInterfaces(DOMElement *elemNetwork)
{
	DOMElement* elemListenerInterfaces=NULL;

	if(elemNetwork == NULL) return E_UNKNOWN;
	ASSERT_NETWORK_OPTIONS_PARENT
		(elemNetwork->getNodeName(), OPTIONS_NODE_LISTENER_INTERFACES);

	getDOMChildByName
		(elemNetwork, OPTIONS_NODE_LISTENER_INTERFACES, elemListenerInterfaces, false);
	m_arListenerInterfaces = CAListenerInterface::getInstance(
		elemListenerInterfaces, m_cnListenerInterfaces);

#ifndef DYNAMIC_MIX

	if (m_cnListenerInterfaces == 0)
	{
		CAMsg::printMsg(LOG_CRIT, "No listener interfaces found!\n");
		return E_UNKNOWN;
	}
#endif
	if(elemListenerInterfaces != NULL)
    {


		appendMixInfo_internal(elemListenerInterfaces, WITH_SUBTREE);
    }
	return E_SUCCESS;
}
