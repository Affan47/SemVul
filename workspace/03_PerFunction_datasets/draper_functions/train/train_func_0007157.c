setTermsAndConditions(DOMElement *elemRoot)
{
	SINT32 ret = E_SUCCESS;
	DOMElement *elemTnCs = NULL;

	if(elemRoot == NULL)
	{
		return E_UNKNOWN;
	}
	ret = getDOMChildByName(elemRoot, OPTION_NODE_TNCS_LIST, elemTnCs, true);
	if(elemTnCs != NULL)
	{
		if(elemTnCs == NULL)
		{
			CAMsg::printMsg(LOG_CRIT,"Could not create the terms and conditions framework document.\n");
			return E_UNKNOWN;
		}
		m_docOpTnCs = createDOMDocument();
		m_docOpTnCs->appendChild(m_docOpTnCs->importNode(elemTnCs, WITH_SUBTREE));
	}
	return E_SUCCESS;
}
