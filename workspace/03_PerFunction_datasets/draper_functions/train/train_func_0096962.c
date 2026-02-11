ParseCMAP_format0  (HPDF_FontDef  fontdef,
                    HPDF_UINT32   offset)
{
    HPDF_TTFontDefAttr attr = (HPDF_TTFontDefAttr)fontdef->attr;
    HPDF_STATUS ret;
    HPDF_BYTE array[256];
    HPDF_UINT size;
    HPDF_UINT16 *parray;
    HPDF_UINT i;

    HPDF_PTRACE((" ParseCMAP_format0\n"));

    ret = HPDF_Stream_Seek (attr->stream, offset, HPDF_SEEK_SET);
    if (ret != HPDF_OK)
        return ret;

    ret += GetUINT16 (attr->stream, &attr->cmap.format);
    ret += GetUINT16 (attr->stream, &attr->cmap.length);
    ret += GetUINT16 (attr->stream, &attr->cmap.language);

    if (ret != HPDF_OK)
        return HPDF_Error_GetCode (fontdef->error);

    if (attr->cmap.format != 0)
        return HPDF_SetError (fontdef->error, HPDF_TTF_INVALID_FOMAT, 0);

    size = 256;
    ret = HPDF_Stream_Read (attr->stream, array, &size);
    if (ret != HPDF_OK)
        return ret;

    attr->cmap.glyph_id_array_count = 256;
    attr->cmap.glyph_id_array = HPDF_GetMem (fontdef->mmgr,
            sizeof (HPDF_UINT16) * 256);
    if (!attr->cmap.glyph_id_array)
        return HPDF_Error_GetCode (fontdef->error);

    parray = attr->cmap.glyph_id_array;
    for (i = 0; i < 256; i++) {
        *parray = attr->cmap.glyph_id_array[i];
        HPDF_PTRACE((" ParseCMAP_format0 glyph_id_array[%d]=%u\n",
                    i, *parray));
        parray++;
    }

    return HPDF_OK;
}
