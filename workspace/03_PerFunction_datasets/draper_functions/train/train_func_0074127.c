make_font(i_ctx_t *i_ctx_p, const gs_matrix * pmat)
{
    os_ptr op = osp;
    os_ptr fp = op - 1;
    gs_font *oldfont, *newfont;
    int code;
    ref *pencoding = 0;

    code = font_param(fp, &oldfont);
    if (code < 0)
        return code;
    {
        uint space = ialloc_space(idmemory);

        ialloc_set_space(idmemory, r_space(fp));
        if (dict_find_string(fp, "Encoding", &pencoding) > 0 &&
            !r_is_array(pencoding)
            )
            code = gs_note_error(e_invalidfont);
        else {


            ref olddict;

            olddict = *pfont_dict(oldfont);
            *pfont_dict(oldfont) = *fp;
            code = gs_makefont(ifont_dir, oldfont, pmat, &newfont);
            *pfont_dict(oldfont) = olddict;
        }
        ialloc_set_space(idmemory, space);
    }
    if (code < 0)
        return code;


    if (pencoding != 0 &&
        !obj_eq(imemory, pencoding, &pfont_data(newfont)->Encoding)
        ) {
        if (newfont->FontType == ft_composite)
            return_error(e_rangecheck);

        ref_assign(&pfont_data(newfont)->Encoding, pencoding);
        lookup_gs_simple_font_encoding((gs_font_base *) newfont);
    }
    *fp = *pfont_dict(newfont);
    pop(1);
    return 0;
}
