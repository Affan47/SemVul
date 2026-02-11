writeXMLToStream_impl(XMLSerializer& xml_stream) const
{
    xml_stream.attribute(Font_xmlHandler::FontSizeAttribute,
                         PropertyHelper::floatToString(d_ptSize));
    if (!d_antiAliased)
        xml_stream.attribute(Font_xmlHandler::FontAntiAliasedAttribute, "False");

    if (d_specificLineSpacing > 0.0f)
        xml_stream.attribute(Font_xmlHandler::FontLineSpacingAttribute,
                             PropertyHelper::floatToString(d_specificLineSpacing));
}
