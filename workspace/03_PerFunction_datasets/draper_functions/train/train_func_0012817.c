pa_getAttributeNodeNS(xmlNode& selfNode,
									  const xmlChar* localName,
									  const xmlChar* namespaceURI)
{
	for(xmlNode* currentNode=(xmlNode*)selfNode.properties;
		currentNode;
		currentNode=currentNode->next)
	{
		if(!namespaceURI || currentNode->ns && xmlStrEqual(currentNode->ns->href, namespaceURI))
			if(!localName || xmlStrEqual(currentNode->name, localName))
				return currentNode;
	}
	return 0;
}
