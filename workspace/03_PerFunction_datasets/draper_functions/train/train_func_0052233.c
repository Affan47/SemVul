AddAttribute(xmlNode* node, const char* attributeName, const char* value)
	{
		if (node != NULL)
		{
			xmlNewProp(node, xcT(attributeName), xcT(value));
		}
	}
