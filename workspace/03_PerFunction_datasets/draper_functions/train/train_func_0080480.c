_jxr_r_LP_QP(jxr_image_t image, struct rbitstream*str)
{
    unsigned q;

    for (q = 0 ; q < image->num_lp_qps ; q += 1) {
        unsigned idx;
        int ch_mode = get_ch_mode(image, str);
        DEBUG(" LP_QP[%u] CH_MODE=%d LP_QUANT=", q, ch_mode);

        switch (ch_mode) {
            case 0:
                image->lp_quant_ch[0][q] = _jxr_rbitstream_uint8(str);
                DEBUG("%d", image->lp_quant_ch[0][q]);
                for (idx = 1 ; idx < image->num_channels ; idx += 1)
                    image->lp_quant_ch[idx][q] = image->lp_quant_ch[0][q];
                break;
            case 1:
                image->lp_quant_ch[0][q] = _jxr_rbitstream_uint8(str);
                image->lp_quant_ch[1][q] = _jxr_rbitstream_uint8(str);
                DEBUG("SEPARATE Y=%d Chr=%d", image->lp_quant_ch[0][q], image->lp_quant_ch[1][q]);
                for (idx = 2 ; idx < image->num_channels ; idx += 1)
                    image->lp_quant_ch[idx][q] = image->lp_quant_ch[1][q];
                break;
            case 2:
                DEBUG("INDEPENDENT =");
                for (idx = 0 ; idx < image->num_channels ; idx += 1) {
                    image->lp_quant_ch[idx][q] = _jxr_rbitstream_uint8(str);
                    DEBUG(" %d", image->lp_quant_ch[idx][q]);
                }
                break;
            case 3:
                break;
            default:
                assert(0);
                break;
        }
        DEBUG("\n");
    }

    return 0;
}
