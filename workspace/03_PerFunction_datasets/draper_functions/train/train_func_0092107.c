ParseHhea (HPDF_FontDef  fontdef)
{
    HPDF_TTFontDefAttr attr = (HPDF_TTFontDefAttr)fontdef->attr;
    HPDF_TTFTable *tbl = FindTable (fontdef, "hhea");
    HPDF_STATUS ret;

    HPDF_PTRACE ((" HPDF_TTFontDef_ParseHhea\n"));

    if (!tbl)
        return HPDF_SetError (fontdef->error, HPDF_TTF_MISSING_TABLE, 6);

    ret = HPDF_Stream_Seek (attr->stream, tbl->offset + 4, HPDF_SEEK_SET);
    if (ret != HPDF_OK)
        return ret;

    ret += GetINT16 (attr->stream, &fontdef->ascent);
    fontdef->ascent = (HPDF_INT16)((HPDF_INT32)fontdef->ascent * 1000 /
                attr->header.units_per_em);
    ret += GetINT16 (attr->stream, &fontdef->descent);
    fontdef->descent = (HPDF_INT16)((HPDF_INT32)fontdef->descent * 1000 /
                attr->header.units_per_em);

    if (ret != HPDF_OK)
        return HPDF_Error_GetCode (fontdef->error);

    ret = HPDF_Stream_Seek (attr->stream, tbl->offset + 34, HPDF_SEEK_SET);
    if (ret != HPDF_OK)
        return ret;

    ret = GetUINT16 (attr->stream, &attr->num_h_metric);
    if (ret != HPDF_OK)
        return HPDF_Error_GetCode (fontdef->error);

    HPDF_PTRACE((" HPDF_TTFontDef_ParseHhea num_h_metric=%u\n",
            attr->num_h_metric));

    return ret;
}
