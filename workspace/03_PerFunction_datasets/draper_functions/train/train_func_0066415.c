getTextRenderArea(void) const
    {
        Scrollbar* vertScrollbar = getVertScrollbar();
        Scrollbar* horzScrollbar = getHorzScrollbar();
        bool v_visible = vertScrollbar->isVisible(true);
        bool h_visible = horzScrollbar->isVisible(true);


        const WidgetLookFeel& wlf = getLookNFeel();

        String area_name(d_frameEnabled ? "WithFrameTextRenderArea" : "NoFrameTextRenderArea");


        if (v_visible || h_visible)
        {
            if (h_visible)
            {
                area_name += "H";
            }
            if (v_visible)
            {
                area_name += "V";
            }
            area_name += "Scroll";
        }

        if (wlf.isNamedAreaDefined(area_name))
        {
            return wlf.getNamedArea(area_name).getArea().getPixelRect(*d_window);
        }


        return wlf.getNamedArea("WithFrameTextRenderArea").getArea().getPixelRect(*d_window);
    }
