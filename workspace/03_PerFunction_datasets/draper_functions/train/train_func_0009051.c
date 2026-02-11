get_ref( pixel *dst,   int *i_dst_stride,
                       pixel *src[4], int i_src_stride,
                       int mvx, int mvy,
                       int i_width, int i_height, const x264_weight_t *weight )
{
    int qpel_idx = ((mvy&3)<<2) + (mvx&3);
    int offset = (mvy>>2)*i_src_stride + (mvx>>2);
    pixel *src1 = src[hpel_ref0[qpel_idx]] + offset + ((mvy&3) == 3) * i_src_stride;

    if( qpel_idx & 5 )
    {
        pixel *src2 = src[hpel_ref1[qpel_idx]] + offset + ((mvx&3) == 3);
        pixel_avg( dst, *i_dst_stride, src1, i_src_stride,
                   src2, i_src_stride, i_width, i_height );
        if( weight->weightfn )
            mc_weight( dst, *i_dst_stride, dst, *i_dst_stride, weight, i_width, i_height );
        return dst;
    }
    else if( weight->weightfn )
    {
        mc_weight( dst, *i_dst_stride, src1, i_src_stride, weight, i_width, i_height );
        return dst;
    }
    else
    {
        *i_dst_stride = i_src_stride;
        return src1;
    }
}
