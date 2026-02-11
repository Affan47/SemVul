WidthText(Font &font, const char *s, int len)
{
    SetFont(font);
    int w;
    int h;

    hDC->GetTextExtent(sci2wx(s, len), &w, &h);
    return w;
}
