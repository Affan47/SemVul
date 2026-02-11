IRasterIO(GDALRWFlag rw, int x0, int y0, int sx, int sy, void *buffer, int bsx, int bsy, GDALDataType bdt, int band_count, int *band_map, int pixel_space, int line_space, int band_space) {
    CPLErr ret;

    if (rw != GF_Read) return CE_Failure;
    if (buffer == NULL) return CE_Failure;
    if ((sx == 0) || (sy == 0) || (bsx == 0) || (bsy == 0) || (band_count == 0)) return CE_None;

    m_hint.m_x0 = x0;
    m_hint.m_y0 = y0;
    m_hint.m_sx = sx;
    m_hint.m_sy = sy;
    m_hint.m_overview = -1;
    m_hint.m_valid = true;

    ret = GDALDataset::IRasterIO(rw, x0, y0, sx, sy, buffer, bsx, bsy, bdt, band_count, band_map, pixel_space, line_space, band_space);
    m_hint.m_valid = false;

    return ret;
}
