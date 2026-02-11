HPDF_Page_SetRGBStroke  (HPDF_Page  page,
                         HPDF_REAL  r,
                         HPDF_REAL  g,
                         HPDF_REAL  b)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_TEXT_OBJECT |
                    HPDF_GMODE_PAGE_DESCRIPTION);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetRGBStroke\n"));

    if (ret != HPDF_OK)
        return ret;

    if (r < 0 || r > 1 || g < 0 || g > 1 || b < 0 || b > 1)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA (pbuf, r, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, g, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, b, eptr);
    HPDF_StrCpy (pbuf, " RG\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->rgb_stroke.r = r;
    attr->gstate->rgb_stroke.g = g;
    attr->gstate->rgb_stroke.b = b;
    attr->gstate->cs_stroke = HPDF_CS_DEVICE_RGB;

    return ret;
}
