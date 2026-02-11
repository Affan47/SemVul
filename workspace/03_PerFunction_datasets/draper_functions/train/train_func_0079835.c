cshow_continue(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    gs_text_enum_t *penum = senum;
    int code;

    check_estack(4);
    code = gs_text_process(penum);
    if (code != TEXT_PROCESS_INTERVENE) {
        code = op_show_continue_dispatch(i_ctx_p, 0, code);
        if (code == o_push_estack)
            make_op_estack(esp - 1, cshow_continue);
        return code;
    }

    {
        ref *pslot = &sslot;
        gs_point wpt;
        gs_font *font = gs_text_current_font(penum);
        gs_font *root_font = gs_rootfont(igs);
        gs_font *scaled_font;
        uint font_space = r_space(pfont_dict(font));
        uint root_font_space = r_space(pfont_dict(root_font));
        int fdepth = penum->fstack.depth;

        gs_text_current_width(penum, &wpt);
        if (font == root_font)
            scaled_font = font;
        else if (fdepth > 0) {


          uint save_space = idmemory->current_space;
          gs_font * immediate_parent = penum->fstack.items[fdepth - 1].font;

          ialloc_set_space(idmemory, font_space);
          code = gs_makefont(font->dir, font,
                             &immediate_parent->FontMatrix,
                             &scaled_font);
          ialloc_set_space(idmemory, save_space);
          if (code < 0)
            return code;
        }
        else {

            uint save_space = idmemory->current_space;

            ialloc_set_space(idmemory, font_space);
            code = gs_makefont(font->dir, font, &root_font->FontMatrix,
                               &scaled_font);
            ialloc_set_space(idmemory, save_space);
            if (code < 0)
                return code;
        }
        push(3);
        make_int(op - 2, gs_text_current_char(penum) & 0xff);
        make_real(op - 1, wpt.x);
        make_real(op, wpt.y);
        make_struct(&ssfont, font_space, font);
        make_struct(&srfont, root_font_space, root_font);
        push_op_estack(cshow_restore_font);

        gs_set_currentfont(igs, scaled_font);
        *++esp = *pslot;
    }
    return o_push_estack;
}
