writeXMLAttributes(XMLSerializer& xml_stream) const
    {

        xml_stream.attribute("name", d_name);

        if (!d_default.empty())
            xml_stream.attribute("initialValue", d_default);

        if (d_writeCausesRedraw)
            xml_stream.attribute("redrawOnWrite", "true");

        if (d_writeCausesLayout)
            xml_stream.attribute("layoutOnWrite", "true");
    }
}
