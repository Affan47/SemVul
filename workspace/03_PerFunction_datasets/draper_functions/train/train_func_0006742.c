findElement(const std::string& attr, const std::string& value, Poco::XML::Node* pNode)
{
	Poco::XML::Node* pRefNode = pNode;
	Poco::XML::Element* pElem = dynamic_cast<Poco::XML::Element*>(pNode);
	if (!(pElem && pElem->getAttribute(attr) == value))
	{
		pNode = pNode->nextSibling();
		while (pNode)
		{
			if (pNode->nodeName() == pRefNode->nodeName())
			{
				pElem = dynamic_cast<Poco::XML::Element*>(pNode);
				if (pElem && pElem->getAttribute(attr) == value) break;
			}
			pNode = pNode->nextSibling();
		}
	}
	return pNode;
}
