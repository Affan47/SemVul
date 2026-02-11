writeXMLElementAttributes_impl(XMLSerializer& xml_stream) const
    {
        if (!d_childSuffix.empty())
            xml_stream.attribute("widget", d_childSuffix);
        xml_stream.attribute("name", d_property);
        if (d_type != DT_INVALID)
            xml_stream.attribute("type", FalagardXMLHelper::dimensionTypeToString(d_type));
    }
