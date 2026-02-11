textst_decode_dialog_style(BITBUFFER *bb, BD_TEXTST_DIALOG_STYLE *p)
{
    unsigned ii;

    p->player_style_flag  = bb_read(bb, 1);
    bb_skip(bb, 15);
    p->region_style_count = bb_read(bb, 8);
    p->user_style_count   = bb_read(bb, 8);

    if (p->region_style_count) {
        p->region_style = calloc(p->region_style_count, sizeof(BD_TEXTST_REGION_STYLE));
        for (ii = 0; ii < p->region_style_count; ii++) {
            _decode_region_style(bb, &p->region_style[ii]);
        }
    }

    if (p->user_style_count) {
        p->user_style = calloc(p->user_style_count, sizeof(BD_TEXTST_USER_STYLE));
        for (ii = 0; ii < p->user_style_count; ii++) {
            _decode_user_style(bb, &p->user_style[ii]);
        }
    }

    _decode_palette(bb, p->palette);

    return 1;
}
