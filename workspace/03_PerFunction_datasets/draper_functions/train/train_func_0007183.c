new_inc_int_info(gs_fapi_server * a_server, gs_fapi_font * a_fapi_font)
{
    ff_server *s = (ff_server *) a_server;

    FT_IncrementalRec *info =
        (FT_IncrementalRec *) FF_alloc(s->ftmemory,
                                       sizeof(FT_IncrementalRec));
    if (info) {
        info->fapi_font = a_fapi_font;
        info->glyph_data = NULL;
        info->glyph_data_length = 0;
        info->glyph_data_in_use = false;
        info->glyph_metrics_index = 0xFFFFFFFF;
        info->metrics_type = gs_fapi_metrics_notdef;
    }
    return info;
}
