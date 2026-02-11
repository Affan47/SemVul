writeColoursXML(XMLSerializer& xml_stream) const
    {

        if (!d_colourPropertyName.empty())
        {
            if (d_colourProperyIsRect)
                xml_stream.openTag("ColourRectProperty");
            else
                xml_stream.openTag("ColourProperty");

            xml_stream.attribute("name", d_colourPropertyName)
                .closeTag();
        }
        else if (!d_colours.isMonochromatic() || d_colours.d_top_left != colour(1,1,1,1))
        {
            xml_stream.openTag("Colours")
                .attribute("topLeft", PropertyHelper::colourToString(d_colours.d_top_left))
                .attribute("topRight", PropertyHelper::colourToString(d_colours.d_top_right))
                .attribute("bottomLeft", PropertyHelper::colourToString(d_colours.d_bottom_left))
                .attribute("bottomRight", PropertyHelper::colourToString(d_colours.d_bottom_right))
                .closeTag();
        }
        else
        {
            return false;
        }
        return true;
    }
