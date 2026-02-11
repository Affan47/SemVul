load_font(const char *fname)
{
    Font *fnt = calloc(1, sizeof(Font));
    if (fnt == 0) {
        fprintf(stderr, tr("ERR: %s: not enough memory\n"), __FUNCTION__);
        exit(1);
    }

    fnt->align = ALIGN_X_LEFT | ALIGN_Y_TOP;
    fnt->color = 0x00FFFFFF;

    font_load_glyphs(fnt, fname);
    return fnt;
}
