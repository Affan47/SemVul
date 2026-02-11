initColoursRect(const Window& wnd, const ColourRect* modCols, ColourRect& cr) const
    {

        if (!d_colourPropertyName.empty())
        {

            if (d_colourProperyIsRect)
            {
                cr = PropertyHelper::stringToColourRect(wnd.getProperty(d_colourPropertyName));
            }

            else
            {
                colour val(PropertyHelper::stringToColour(wnd.getProperty(d_colourPropertyName)));
                cr.d_top_left     = val;
                cr.d_top_right    = val;
                cr.d_bottom_left  = val;
                cr.d_bottom_right = val;
            }
        }

        else
        {
            cr = d_colours;
        }

        if (modCols)
        {
            cr *= *modCols;
        }
    }
