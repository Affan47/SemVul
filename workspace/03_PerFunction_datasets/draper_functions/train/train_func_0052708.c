read_dqt_marker()
{
    int n, i, prec;
    uint num_left;
    uint temp;

    num_left = get_bits(16);

    if (num_left < 2) {
        stop_decoding(JPGD_BAD_DQT_MARKER);
    }

    num_left -= 2;

    while (num_left) {
        n = get_bits(8);
        prec = n >> 4;
        n &= 0x0F;

        if (n >= JPGD_MAX_QUANT_TABLES) {
            stop_decoding(JPGD_BAD_DQT_TABLE);
        }

        if (!m_quant[n]) {
            m_quant[n] = (jpgd_quant_t *)alloc(64 * sizeof(jpgd_quant_t));
        }


        for (i = 0; i < 64; i++) {
            temp = get_bits(8);

            if (prec) {
                temp = (temp << 8) + get_bits(8);
            }

            m_quant[n][i] = static_cast<jpgd_quant_t>(temp);
        }

        i = 64 + 1;

        if (prec) {
            i += 64;
        }

        if (num_left < (uint)i) {
            stop_decoding(JPGD_BAD_DQT_LENGTH);
        }

        num_left -= i;
    }
}
