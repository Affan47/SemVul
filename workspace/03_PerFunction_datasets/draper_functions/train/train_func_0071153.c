x264_noise_reduction_update( x264_t *h )
{
    h->nr_offset = h->nr_offset_denoise;
    h->nr_residual_sum = h->nr_residual_sum_buf[0];
    h->nr_count = h->nr_count_buf[0];
    for( int cat = 0; cat < 3 + CHROMA444; cat++ )
    {
        int dct8x8 = cat&1;
        int size = dct8x8 ? 64 : 16;
        const uint32_t *weight = dct8x8 ? x264_dct8_weight2_tab : x264_dct4_weight2_tab;

        if( h->nr_count[cat] > (dct8x8 ? (1<<16) : (1<<18)) )
        {
            for( int i = 0; i < size; i++ )
                h->nr_residual_sum[cat][i] >>= 1;
            h->nr_count[cat] >>= 1;
        }

        for( int i = 0; i < size; i++ )
            h->nr_offset[cat][i] =
                ((uint64_t)h->param.analyse.i_noise_reduction * h->nr_count[cat]
                 + h->nr_residual_sum[cat][i]/2)
              / ((uint64_t)h->nr_residual_sum[cat][i] * weight[i]/256 + 1);


        h->nr_offset[cat][0] = 0;
    }
}
