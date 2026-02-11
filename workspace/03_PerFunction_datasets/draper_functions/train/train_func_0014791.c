writeXML(STD_NAMESPACE ostream &stream,
                                          const size_t flags) const
{
    OFString tmpString;
    OFCondition result = EC_Normal;
    writeXMLItemStart(stream, flags);
    result = DSRDocumentTreeNode::writeXML(stream, flags);

    DcmDateTime::getISOFormattedDateTimeFromString(getValue(), tmpString, OFTrue , OFFalse ,
        OFFalse , OFFalse , "T" );
    writeStringValueToXML(stream, tmpString, "value", (flags & XF_writeEmptyTags) > 0);
    writeXMLItemEnd(stream, flags);
    return result;
}
