Type1Font_TextWidth  (HPDF_Font        font,
                      const HPDF_BYTE  *text,
                      HPDF_UINT        len)
{
    HPDF_FontAttr attr = (HPDF_FontAttr)font->attr;
    HPDF_TextWidth ret = {0, 0, 0, 0};
    HPDF_UINT i;
    HPDF_BYTE b = 0;

    HPDF_PTRACE ((" HPDF_Type1Font_TextWidth\n"));

    if (attr->widths) {
        for (i = 0; i < len; i++) {
            b = text[i];
            ret.numchars++;
            ret.width += attr->widths[b];

            if (HPDF_IS_WHITE_SPACE(b)) {
                ret.numspace++;
                ret.numwords++;
            }
        }
    } else
        HPDF_SetError (font->error, HPDF_FONT_INVALID_WIDTHS_TABLE, 0);


    if (HPDF_IS_WHITE_SPACE(b))
        ;
    else
        ret.numwords++;

    return ret;
}
