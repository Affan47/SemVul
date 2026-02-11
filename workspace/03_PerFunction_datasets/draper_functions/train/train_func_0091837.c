load_mcu_YCC(const uint8 *pSrc, int width, int bpp, int y)
{
    if (bpp == 4) {
        RGB_to_YCC(m_image, reinterpret_cast<const rgba *>(pSrc), width, y);
    } else if (bpp == 3) {
        RGB_to_YCC(m_image, reinterpret_cast<const rgb *>(pSrc), width, y);
    } else {
        Y_to_YCC(m_image, pSrc, width, y);
    }


    for(int c=0; c < m_num_components; c++) {
        const float lastpx = m_image[c].get_px(width - 1, y);
        for (int x = width; x < m_image[0].m_x; x++) {
            m_image[c].set_px(lastpx, x, y);
        }
    }
}
