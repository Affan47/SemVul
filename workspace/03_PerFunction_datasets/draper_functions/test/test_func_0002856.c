setCurrentTimeMilliesAsDOMAttribute(DOMNode *pElem)
{
		if( pElem == NULL || pElem->getNodeType() != DOMNode::ELEMENT_NODE )
		{
			return E_UNKNOWN;
		}
		UINT64 currentMillis;
		getcurrentTimeMillis(currentMillis);
		UINT8 tmpStrCurrentMillis[50];
		print64(tmpStrCurrentMillis,currentMillis);
		setDOMElementAttribute
			(pElem,UNIVERSAL_ATTRIBUTE_LAST_UPDATE, tmpStrCurrentMillis );
		return E_SUCCESS;

}
