pdf_add_ToUnicode(gx_device_pdf *pdev, gs_font *font, pdf_font_resource_t *pdfont,
                  gs_glyph glyph, gs_char ch, const gs_const_string *gnstr)
{   int code;
    gs_char unicode;

    if (glyph == GS_NO_GLYPH)
        return 0;
    unicode = font->procs.decode_glyph((gs_font *)font, glyph, ch);
    if (unicode == GS_NO_CHAR && gnstr != NULL && gnstr->size == 7) {
        if (!memcmp(gnstr->data, "uni", 3)) {
            static const char *hexdigits = "0123456789ABCDEF";
            char *d0 = strchr(hexdigits, gnstr->data[3]);
            char *d1 = strchr(hexdigits, gnstr->data[4]);
            char *d2 = strchr(hexdigits, gnstr->data[5]);
            char *d3 = strchr(hexdigits, gnstr->data[6]);

            if (d0 != NULL && d1 != NULL && d2 != NULL && d3 != NULL)
                unicode = ((d0 - hexdigits) << 12) + ((d1 - hexdigits) << 8) +
                          ((d2 - hexdigits) << 4 ) +  (d3 - hexdigits);
        }
    }
    if (unicode != GS_NO_CHAR) {
        if (pdfont->cmap_ToUnicode == NULL) {


            uint num_codes = 256, key_size = 1;

            if (font->FontType == ft_CID_encrypted) {
                gs_font_cid0 *pfcid = (gs_font_cid0 *)font;

                num_codes = pfcid->cidata.common.CIDCount;
                key_size = 2;
            } else if (font->FontType == ft_CID_TrueType || font->FontType == ft_composite) {
                key_size = 2;
#ifdef DEPRECATED_906
                gs_font_cid2 *pfcid = (gs_font_cid2 *)font;

                num_codes = pfcid->cidata.common.CIDCount;
#else


                num_codes = 65536;
#endif
            }
            code = gs_cmap_ToUnicode_alloc(pdev->pdf_memory, pdfont->rid, num_codes, key_size,
                                            &pdfont->cmap_ToUnicode);
            if (code < 0)
                return code;
        }
        if (pdfont->cmap_ToUnicode != NULL)
            gs_cmap_ToUnicode_add_pair(pdfont->cmap_ToUnicode, ch, unicode);
    }
    return 0;
}
