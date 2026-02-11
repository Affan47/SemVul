writeXMLToStream_impl (XMLSerializer& xml_stream) const
{
    float advscale = 1.0f / d_origHorzScaling;
    for (CodepointMap::const_iterator i = d_cp_map.begin(); i != d_cp_map.end(); ++i)
    {
        xml_stream.openTag("Mapping")
            .attribute(Font_xmlHandler::MappingCodepointAttribute,
                       PropertyHelper::uintToString(i->first))
            .attribute(Font_xmlHandler::MappingHorzAdvanceAttribute,
                       PropertyHelper::floatToString(i->second.getAdvance() * advscale))
            .attribute(Font_xmlHandler::MappingImageAttribute,
                       i->second.getImage()->getName());

        xml_stream.closeTag();
    }
}
