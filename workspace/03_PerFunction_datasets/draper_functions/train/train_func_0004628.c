charstring_execchar(i_ctx_t *i_ctx_p, int font_type_mask)
{
    gs_text_enum_t *penum = op_show_find(i_ctx_p);
    gs_font *pfont;
    os_ptr op = osp;
    int code = font_param(op - 3, &pfont);

    if (code < 0)
        return code;
    if (penum == 0 ||
        pfont->FontType >= sizeof(font_type_mask) * 8 ||
        !(font_type_mask & (1 << (int)pfont->FontType)))
        return_error(e_undefined);
    code = charstring_execchar_aux(i_ctx_p, penum, pfont);
    if (code < 0 && igs->in_cachedevice == CACHE_DEVICE_CACHING) {


        gs_show_enum *const penum_s = (gs_show_enum *)penum;

        if (penum_s->cc != NULL) {
            gx_free_cached_char(pfont->dir, penum_s->cc);
            penum_s->cc = NULL;
        }
    }
    return code;
}
