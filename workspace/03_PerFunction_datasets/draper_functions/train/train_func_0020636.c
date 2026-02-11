x264_frame_expand_border_mod16( x264_t *h, x264_frame_t *frame )
{
    for( int i = 0; i < frame->i_plane; i++ )
    {
        int i_width = h->param.i_width;
        int h_shift = i && CHROMA_H_SHIFT;
        int v_shift = i && CHROMA_V_SHIFT;
        int i_height = h->param.i_height >> v_shift;
        int i_padx = (h->mb.i_mb_width * 16 - h->param.i_width);
        int i_pady = (h->mb.i_mb_height * 16 - h->param.i_height) >> v_shift;

        if( i_padx )
        {
            for( int y = 0; y < i_height; y++ )
                pixel_memset( &frame->plane[i][y*frame->i_stride[i] + i_width],
                              &frame->plane[i][y*frame->i_stride[i] + i_width - 1-h_shift],
                              i_padx>>h_shift, sizeof(pixel)<<h_shift );
        }
        if( i_pady )
        {
            for( int y = i_height; y < i_height + i_pady; y++ )
                memcpy( &frame->plane[i][y*frame->i_stride[i]],
                        &frame->plane[i][(i_height-(~y&PARAM_INTERLACED)-1)*frame->i_stride[i]],
                        (i_width + i_padx) * sizeof(pixel) );
        }
    }
}
