writeXML(STD_NAMESPACE ostream &stream,
                                          const size_t flags) const
{
    OFCondition result = EC_Normal;
    writeXMLItemStart(stream, flags);
    result = DSRDocumentTreeNode::writeXML(stream, flags);
    stream << "<value>" << OFendl;
    DSRWaveformReferenceValue::writeXML(stream, flags);
    stream << "</value>" << OFendl;
    writeXMLItemEnd(stream, flags);
    return result;
}
