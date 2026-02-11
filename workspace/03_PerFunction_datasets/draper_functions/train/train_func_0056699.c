x264_cabac_intra4x4_pred_mode( x264_cabac_t *cb, int i_pred, int i_mode )
{
    if( i_pred == i_mode )
        x264_cabac_encode_decision( cb, 68, 1 );
    else
    {
        x264_cabac_encode_decision( cb, 68, 0 );
        if( i_mode > i_pred  )
            i_mode--;
        x264_cabac_encode_decision( cb, 69, (i_mode     )&0x01 );
        x264_cabac_encode_decision( cb, 69, (i_mode >> 1)&0x01 );
        x264_cabac_encode_decision( cb, 69, (i_mode >> 2)      );
    }
}
