HPDF_Page_ShowText  (HPDF_Page    page,
                     const char  *text)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;
    HPDF_REAL tw;

    HPDF_PTRACE ((" HPDF_Page_ShowText\n"));

    if (ret != HPDF_OK || text == NULL || text[0] == 0)
        return ret;

    attr = (HPDF_PageAttr)page->attr;


    if (!attr->gstate->font)
        return HPDF_RaiseError (page->error, HPDF_PAGE_FONT_NOT_FOUND, 0);

    tw = HPDF_Page_TextWidth (page, text);
    if (!tw)
        return ret;

    if (InternalWriteText (attr, text) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " Tj\012") != HPDF_OK)
        return HPDF_CheckError (page->error);


    if (attr->gstate->writing_mode == HPDF_WMODE_HORIZONTAL) {
        attr->text_pos.x += tw * attr->text_matrix.a;
        attr->text_pos.y += tw * attr->text_matrix.b;
    } else {
        attr->text_pos.x -= tw * attr->text_matrix.b;
        attr->text_pos.y -= tw * attr->text_matrix.a;
    }

    return ret;
}
