msmpeg4_encode_picture_header(MpegEncContext * s, int picture_number)
{
    find_best_tables(s);

    align_put_bits(&s->pb);
    put_bits(&s->pb, 2, s->pict_type - 1);

    put_bits(&s->pb, 5, s->qscale);
    if(s->msmpeg4_version<=2){
        s->rl_table_index = 2;
        s->rl_chroma_table_index = 2;
    }

    s->dc_table_index = 1;
    s->mv_table_index = 1;
    s->use_skip_mb_code = 1;
    s->per_mb_rl_table = 0;
    if(s->msmpeg4_version==4)
        s->inter_intra_pred= (s->width*s->height < 320*240 && s->bit_rate<=II_BITRATE && s->pict_type==FF_P_TYPE);


    if (s->pict_type == FF_I_TYPE) {
        s->slice_height= s->mb_height/1;
        put_bits(&s->pb, 5, 0x16 + s->mb_height/s->slice_height);

        if(s->msmpeg4_version==4){
            msmpeg4_encode_ext_header(s);
            if(s->bit_rate>MBAC_BITRATE)
                put_bits(&s->pb, 1, s->per_mb_rl_table);
        }

        if(s->msmpeg4_version>2){
            if(!s->per_mb_rl_table){
                ff_msmpeg4_code012(&s->pb, s->rl_chroma_table_index);
                ff_msmpeg4_code012(&s->pb, s->rl_table_index);
            }

            put_bits(&s->pb, 1, s->dc_table_index);
        }
    } else {
        put_bits(&s->pb, 1, s->use_skip_mb_code);

        if(s->msmpeg4_version==4 && s->bit_rate>MBAC_BITRATE)
            put_bits(&s->pb, 1, s->per_mb_rl_table);

        if(s->msmpeg4_version>2){
            if(!s->per_mb_rl_table)
                ff_msmpeg4_code012(&s->pb, s->rl_table_index);

            put_bits(&s->pb, 1, s->dc_table_index);

            put_bits(&s->pb, 1, s->mv_table_index);
        }
    }

    s->esc3_level_length= 0;
    s->esc3_run_length= 0;

#ifdef DEBUG
    intra_count = 0;
    av_log(s->avctx, AV_LOG_DEBUG, "*****frame %d:\n", frame_count++);
#endif
}
