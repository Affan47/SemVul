writeXMLToStream(XMLSerializer& xml_stream) const
    {
        xml_stream.openTag("Dim")
            .attribute("type", FalagardXMLHelper::dimensionTypeToString(d_type));

        if (d_value)
            d_value->writeXMLToStream(xml_stream);
        xml_stream.closeTag();
    }
