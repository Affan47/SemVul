zbuildfont2(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    charstring_font_refs_t refs;
    build_proc_refs build;
    int code = build_proc_name_refs(imemory, &build,
                                    "%Type2BuildChar", "%Type2BuildGlyph");
    gs_type1_data data1;

    if (code < 0)
        return code;
    code = charstring_font_get_refs(op, &refs);
    if (code < 0)
        return code;
    code = type2_font_params(op, &refs, &data1);
    if (code < 0)
        return code;
    return build_charstring_font(i_ctx_p, op, &build, ft_encrypted2, &refs,
                                 &data1, bf_notdef_required);
}
