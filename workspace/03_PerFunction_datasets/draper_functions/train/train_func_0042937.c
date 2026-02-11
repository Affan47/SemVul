x264_cabac_mb_type_intra( x264_t *h, x264_cabac_t *cb, int i_mb_type,
                    int ctx0, int ctx1, int ctx2, int ctx3, int ctx4, int ctx5 )
{
    if( i_mb_type == I_4x4 || i_mb_type == I_8x8 )
    {
        x264_cabac_encode_decision_noup( cb, ctx0, 0 );
    }
#if !RDO_SKIP_BS
    else if( i_mb_type == I_PCM )
    {
        x264_cabac_encode_decision_noup( cb, ctx0, 1 );
        x264_cabac_encode_flush( h, cb );
    }
#endif
    else
    {
        int i_pred = x264_mb_pred_mode16x16_fix[h->mb.i_intra16x16_pred_mode];

        x264_cabac_encode_decision_noup( cb, ctx0, 1 );
        x264_cabac_encode_terminal( cb );

        x264_cabac_encode_decision_noup( cb, ctx1, !!h->mb.i_cbp_luma );
        if( h->mb.i_cbp_chroma == 0 )
            x264_cabac_encode_decision_noup( cb, ctx2, 0 );
        else
        {
            x264_cabac_encode_decision( cb, ctx2, 1 );
            x264_cabac_encode_decision_noup( cb, ctx3, h->mb.i_cbp_chroma>>1 );
        }
        x264_cabac_encode_decision( cb, ctx4, i_pred>>1 );
        x264_cabac_encode_decision_noup( cb, ctx5, i_pred&1 );
    }
}
