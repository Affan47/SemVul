_jxr_r_TILE_HEADER_LOWPASS(jxr_image_t image, struct rbitstream*str,
                                int alpha_flag,
                                unsigned tx, unsigned ty)
{
    DEBUG(" TILE_HEADER_LOWPASS START bitpos=%zu\n", _jxr_rbitstream_bitpos(str));
    if (image->lp_frame_uniform == 0) {
        image->lp_use_dc_qp = _jxr_rbitstream_uint1(str);
        DEBUG(" TILE_HEADER_LP: parse non-uniform LP_QP: USE_DC_QP=%u\n",
            image->lp_use_dc_qp);
        if (image->lp_use_dc_qp == 0) {
            image->num_lp_qps = _jxr_rbitstream_uint4(str) + 1;
            DEBUG(" TILE_HEADER_LP: NUM_LP_QPS = %d\n", image->num_lp_qps);
            _jxr_r_LP_QP(image, str);
            memcpy(image->tile_quant[ty*(image->tile_columns) + tx].lp_quant_ch, image->lp_quant_ch, MAX_CHANNELS*MAX_LP_QPS);
        }
        else
        {

            int ch;
            for(ch = 0; ch < image->num_channels; ch++)
                image->tile_quant[ty*(image->tile_columns) + tx].lp_quant_ch[ch][0] = image->dc_quant_ch[ch];
        }
    }
}
