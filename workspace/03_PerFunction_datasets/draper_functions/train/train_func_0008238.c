_preload_textst_subpath(BLURAY *bd)
{
    uint8_t        char_code      = BLURAY_TEXT_CHAR_CODE_UTF8;
    int            textst_subpath = -1;
    unsigned       textst_subclip = 0;
    uint16_t       textst_pid     = 0;
    unsigned       ii;

    if (!bd->graphics_controller) {
        return 0;
    }

    if (!bd->decode_pg || !bd->title) {
        return 0;
    }

    _find_pg_stream(bd, &textst_pid, &textst_subpath, &textst_subclip, &char_code);
    if (textst_subpath < 0) {
        return 0;
    }

    if (textst_subclip >= bd->title->sub_path[textst_subpath].clip_list.count) {
        BD_DEBUG(DBG_BLURAY | DBG_CRIT, "_preload_textst_subpath(): invalid subclip id\n");
        return -1;
    }

    if (bd->st_textst.clip == &bd->title->sub_path[textst_subpath].clip_list.clip[textst_subclip]) {
        BD_DEBUG(DBG_BLURAY, "_preload_textst_subpath(): subpath already loaded");
        return 1;
    }

    gc_run(bd->graphics_controller, GC_CTRL_PG_RESET, 0, NULL);

    bd->st_textst.clip = &bd->title->sub_path[textst_subpath].clip_list.clip[textst_subclip];

    if (!_preload_m2ts(bd, &bd->st_textst)) {
        _close_preload(&bd->st_textst);
        return 0;
    }

    gc_decode_ts(bd->graphics_controller, 0x1800, bd->st_textst.buf, SPN(bd->st_textst.clip_size) / 32, -1);


    gc_add_font(bd->graphics_controller, NULL);
    for (ii = 0; ii < bd->st_textst.clip->cl->font_info.font_count; ii++) {
        char *file = str_printf("%s/BDMV/AUXDATA/%s.otf", bd->device_path, bd->st_textst.clip->cl->font_info.font[ii].file_id);
        gc_add_font(bd->graphics_controller, file);
        X_FREE(file);
    }
    gc_run(bd->graphics_controller, GC_CTRL_PG_CHARCODE, char_code, NULL);


    _init_textst_timer(bd);

    return 1;
}
