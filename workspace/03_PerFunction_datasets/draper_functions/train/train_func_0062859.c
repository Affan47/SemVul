sftk_DestroyAttribute(SFTKAttribute *attribute)
{
    if (attribute->freeData) {
	if (attribute->attrib.pValue) {


	    PORT_Memset(attribute->attrib.pValue, 0,
						attribute->attrib.ulValueLen);
	}
	PORT_Free(attribute->attrib.pValue);
    }
    PORT_Free(attribute);
}
