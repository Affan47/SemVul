ReadNodePropertyCRC(xmlNode* node, const char* property)
	{
		FUCrc32::crc32 ret = 0;
		if (node != NULL && property != NULL)
		{
			xmlChar* data = xmlGetProp(node, xmlT(property));
			if (data != NULL)
			{
				ret = FUCrc32::CRC32((const char*) data);
				xmlFree(data);
			}
		}
		return ret;
	}
