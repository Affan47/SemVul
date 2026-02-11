copied_data_alloc(gs_font *copied, stream *s, uint extra, int code)
{
    gs_copied_font_data_t *const cfdata = cf_data(copied);
    uint len = stell(s);
    byte *fdata;

    if (code < 0)
        return code;
    fdata = gs_alloc_bytes(copied->memory, len + extra, "copied_data_alloc");
    if (fdata == 0)
        return_error(gs_error_VMerror);
    s_init(s, copied->memory);
    swrite_string(s, fdata, len);
    cfdata->data = fdata;
    cfdata->data_size = len + extra;
    return 0;
}
