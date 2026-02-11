expanded_convert()
{
    int row = m_max_mcu_y_size - m_mcu_lines_left;

    uint8 *Py = m_pSample_buf + (row / 8) * 64 * m_comp_h_samp[0] + (row & 7) * 8;

    uint8 *d = m_pScan_line_0;

    for (int i = m_max_mcus_per_row; i > 0; i--) {
        for (int k = 0; k < m_max_mcu_x_size; k += 8) {
            const int Y_ofs = k * 8;
            const int Cb_ofs = Y_ofs + 64 * m_expanded_blocks_per_component;
            const int Cr_ofs = Y_ofs + 64 * m_expanded_blocks_per_component * 2;
            for (int j = 0; j < 8; j++) {
                int y = Py[Y_ofs + j];
                int cb = Py[Cb_ofs + j];
                int cr = Py[Cr_ofs + j];

                d[0] = clamp(y + m_crr[cr]);
                d[1] = clamp(y + ((m_crg[cr] + m_cbg[cb]) >> 16));
                d[2] = clamp(y + m_cbb[cb]);
                d[3] = 255;

                d += 4;
            }
        }

        Py += 64 * m_expanded_blocks_per_mcu;
    }
}
