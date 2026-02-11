writeXML(STD_NAMESPACE ostream &stream,
                                          const size_t flags) const
{
    OFCondition result = EC_Normal;
    writeXMLItemStart(stream, flags, OFFalse );
    stream << " type=\"" << graphicType3DToEnumeratedValue(getGraphicType()) << "\"";
    stream << ">" << OFendl;
    result = DSRDocumentTreeNode::writeXML(stream, flags);
    DSRSpatialCoordinates3DValue::writeXML(stream, flags);
    writeXMLItemEnd(stream, flags);
    return result;
}
