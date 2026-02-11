getElementFromAttribute(const DSRXMLCursor &cursor,
                                                    DcmElement &delem,
                                                    const char *name,
                                                    const OFBool encoding,
                                                    const OFBool required) const
{
    OFCondition result = SR_EC_InvalidDocument;

    if ((cursor.Node != NULL) && (name != NULL) && (strlen(name) > 0))
    {

        xmlChar *attrVal = xmlGetProp(cursor.Node, OFreinterpret_cast(const xmlChar *, name));
        if ((attrVal != NULL) && (xmlStrlen(attrVal) > 0))
        {
            OFString attrStr;

            if (encoding && convertUtf8ToCharset(attrVal, attrStr))
                result = delem.putString(attrStr.c_str());
            else
                result = delem.putString(OFreinterpret_cast(const char *, attrVal));
        } else if (required)
            printMissingAttributeError(cursor, name);

        xmlFree(attrVal);
    }
    return result;
}
