simple_glyph_metrics(gs_font_type42 * pfont, uint glyph_index, int wmode,
                     float sbw[4])
{
    double factor = 1.0 / pfont->data.unitsPerEm;
    uint width;
    int lsb;
    int code;

    {
        const gs_type42_mtx_t *pmtx = &pfont->data.metrics[wmode];
        uint num_metrics = pmtx->numMetrics;
        byte pmetrics[4];

        if (pmtx->length == 0)
            return_error(gs_error_rangecheck);
        if (glyph_index < num_metrics) {
            READ_SFNTS(pfont, pmtx->offset + glyph_index * 4, 4, pmetrics);
            width = U16(pmetrics);
            lsb = S16(pmetrics + 2);
        } else {
            uint offset = pmtx->offset + num_metrics * 4;
            uint glyph_offset = (glyph_index - num_metrics) * 2;
            byte plsb[2];

            READ_SFNTS(pfont, offset - 4, 4, pmetrics);
            width = U16(pmetrics);
            if (glyph_offset >= pmtx->length)
                glyph_offset = pmtx->length - 2;
            READ_SFNTS(pfont, offset + glyph_offset, 2, plsb);
            lsb = S16(plsb);
        }
    }
    if (wmode) {
        factor = -factor;
        sbw[0] = 0, sbw[1] = lsb * factor;
        sbw[2] = 0, sbw[3] = width * factor;
    } else {
        sbw[0] = lsb * factor, sbw[1] = 0;
        sbw[2] = width * factor, sbw[3] = 0;
    }
    return 0;
}
