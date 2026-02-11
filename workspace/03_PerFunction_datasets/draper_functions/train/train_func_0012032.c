zglyphshow(i_ctx_t *i_ctx_p)
{
    gs_glyph glyph;
    gs_text_enum_t *penum;
    int code;

    if ((code = glyph_show_setup(i_ctx_p, &glyph)) != 0 ||
        (code = gs_glyphshow_begin(igs, glyph, imemory_local, &penum)) < 0)
        return code;
    *(op_proc_t *)&penum->enum_client_data = zglyphshow;
    if ((code = op_show_finish_setup(i_ctx_p, penum, 1, NULL)) < 0) {
        ifree_object(penum, "zglyphshow");
        return code;
    }
    return op_show_continue_pop(i_ctx_p, 1);
}
