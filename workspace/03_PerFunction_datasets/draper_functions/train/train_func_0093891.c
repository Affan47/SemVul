getReadonlyColour()
{
    static wxColour colourReadOnly;
    if (!colourReadOnly.IsOk())
    {


        wxColour clWnd(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
        int r1 = clWnd.Red(), g1 = clWnd.Green(), b1 = clWnd.Blue();
        wxColour clBtn = wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE);
        int r2 = clBtn.Red(), g2 = clBtn.Green(), b2 = clBtn.Blue();
        int distance = abs(r1 - r2) + abs(g1 - g2) + abs(b1 - b2);
        if (distance >= 72)
        {


            int scale = (distance >= 192) ? distance / 64 : 2;
            colourReadOnly.Set(r1 + (r2 - r1) / scale,
                g1 + (g2 - g1) / scale, b1 + (b2 - b1) / scale);
        }
        else
        {


            RgbHsvConversion rgbhsv(clWnd);
            rgbhsv.setValue(std::max(0.0, rgbhsv.getValue() - 0.05));
            colourReadOnly = rgbhsv.getColour();
        }
    }
    return colourReadOnly;
}
