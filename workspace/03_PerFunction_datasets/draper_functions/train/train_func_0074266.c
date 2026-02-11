build_gs_TrueType_font(i_ctx_t *i_ctx_p, os_ptr op, gs_font_type42 **ppfont,
                       font_type ftype, gs_memory_type_ptr_t pstype,
                       const char *bcstr, const char *bgstr,
                       build_font_options_t options)
{
    build_proc_refs build;
    ref sfnts, GlyphDirectory;
    gs_font_type42 *pfont;
    font_data *pdata;
    int code;

    code = build_proc_name_refs(imemory, &build, bcstr, bgstr);
    if (code < 0)
        return code;
    check_type(*op, t_dictionary);


    if ((code = font_string_array_param(imemory, op, "sfnts", &sfnts)) < 0 ||
        (code = font_GlyphDirectory_param(op, &GlyphDirectory)) < 0
        )
        return code;
    code = build_gs_primitive_font(i_ctx_p, op, (gs_font_base **)ppfont,
                                   ftype, pstype, &build, options);
    if (code != 0)
        return code;
    pfont = *ppfont;
    pdata = pfont_data(pfont);
    ref_assign(&pdata->u.type42.sfnts, &sfnts);
    pdata->u.type42.mru_sfnts_index = 0;
    pdata->u.type42.mru_sfnts_pos = 0;
    make_null_new(&pdata->u.type42.CIDMap);
    ref_assign(&pdata->u.type42.GlyphDirectory, &GlyphDirectory);
    pfont->data.string_proc = z42_string_proc;
    pfont->data.proc_data = (char *)pdata;
    pfont->is_resource = (options & bf_has_font_file ? true : false);
    code = gs_type42_font_init(pfont, 0);
    if (code < 0)
        return code;
    pfont->procs.font_info = z42_font_info;


    if (!r_has_type(&GlyphDirectory, t_null)) {
        pfont->data.get_outline = z42_gdir_get_outline;
        pfont->procs.enumerate_glyph = z42_gdir_enumerate_glyph;
    } else
        pfont->procs.enumerate_glyph = z42_enumerate_glyph;


    pfont->data.get_glyph_index = z42_get_glyph_index;
    pfont->data.substitute_glyph_index_vertical = gs_type42_substitute_glyph_index_vertical;
    pfont->procs.encode_char = z42_encode_char;
    pfont->procs.glyph_info = z42_glyph_info;
    pfont->procs.glyph_outline = z42_glyph_outline;
    return 0;
}
