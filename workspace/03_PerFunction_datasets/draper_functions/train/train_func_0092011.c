LoadTTFontFromStream2 (HPDF_Doc         pdf,
                       HPDF_Stream      font_data,
                       HPDF_UINT        index,
                       HPDF_BOOL        embedding,
                       const char      *file_name)
{
    HPDF_FontDef def;

    HPDF_PTRACE ((" HPDF_LoadTTFontFromStream2\n"));
    HPDF_UNUSED (file_name);

    def = HPDF_TTFontDef_Load2 (pdf->mmgr, font_data, index, embedding);
    if (def) {
        HPDF_FontDef  tmpdef = HPDF_Doc_FindFontDef (pdf, def->base_font);
        if (tmpdef) {
            HPDF_FontDef_Free (def);
            return tmpdef->base_font;
        }

        if (HPDF_List_Add (pdf->fontdef_list, def) != HPDF_OK) {
            HPDF_FontDef_Free (def);
            return NULL;
        }
    } else
        return NULL;

    if (embedding) {
        if (pdf->ttfont_tag[0] == 0) {
            HPDF_MemCpy (pdf->ttfont_tag, (HPDF_BYTE *)"HPDFAA", 6);
        } else {
            HPDF_INT i;

            for (i = 5; i >= 0; i--) {
                pdf->ttfont_tag[i] += 1;
                if (pdf->ttfont_tag[i] > 'Z')
                    pdf->ttfont_tag[i] = 'A';
                else
                    break;
            }
        }

        HPDF_TTFontDef_SetTagName (def, (char *)pdf->ttfont_tag);
    }

    return def->base_font;
}
