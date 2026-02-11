mch_print_set_font(iBold, iItalic, iUnderline)
    int		iBold;
    int		iItalic;
    int		iUnderline;
{
    int		font = 0;

    if (iBold)
	font |= 0x01;
    if (iItalic)
	font |= 0x02;

    if (font != prt_font)
    {
	prt_font = font;
	prt_attribute_change = TRUE;
	prt_need_font = TRUE;
    }
    if (prt_underline != iUnderline)
    {
	prt_underline = iUnderline;
	prt_attribute_change = TRUE;
	prt_need_underline = TRUE;
    }
}
