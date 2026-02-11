readXML(const DSRXMLDocument &doc,
                                               DSRXMLCursor cursor)
{

    OFCondition result = DSRCompositeReferenceValue::readXML(doc, cursor);

    if (result.good())
    {

        cursor = doc.getNamedNode(cursor.getChild(), "channels");
        if (cursor.valid())
        {
            OFString tmpString;

            result = ChannelList.putString(doc.getStringFromNodeContent(cursor, tmpString).c_str());
        }
    }
    return result;
}
