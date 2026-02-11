gs_type0_define_font(gs_font_dir * pdir, gs_font * pfont)
{
    const gs_matrix *pmat = &pfont->FontMatrix;


    if (pmat->xx == 1.0 && pmat->yy == 1.0 &&
        pmat->xy == 0.0 && pmat->yx == 0.0 &&
        pmat->tx == 0.0 && pmat->ty == 0.0
        )
        return 0;
    return gs_type0_adjust_matrix(pdir, (gs_font_type0 *) pfont, pmat);
}
