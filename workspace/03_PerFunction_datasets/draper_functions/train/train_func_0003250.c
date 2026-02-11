encode_init(AVCodecContext *avctx)
{
    MpegEncContext *s = avctx->priv_data;

    if(MPV_encode_init(avctx) < 0)
        return -1;

    if(find_frame_rate_index(s) < 0){
        if(s->strict_std_compliance > FF_COMPLIANCE_EXPERIMENTAL){
            av_log(avctx, AV_LOG_ERROR, "MPEG1/2 does not support %d/%d fps\n", avctx->time_base.den, avctx->time_base.num);
            return -1;
        }else{
            av_log(avctx, AV_LOG_INFO, "MPEG1/2 does not support %d/%d fps, there may be AV sync issues\n", avctx->time_base.den, avctx->time_base.num);
        }
    }

    if(avctx->profile == FF_PROFILE_UNKNOWN){
        if(avctx->level != FF_LEVEL_UNKNOWN){
            av_log(avctx, AV_LOG_ERROR, "Set profile and level\n");
            return -1;
        }
        avctx->profile = s->chroma_format == CHROMA_420 ? 4 : 0;
    }

    if(avctx->level == FF_LEVEL_UNKNOWN){
        if(avctx->profile == 0){
            if(avctx->width <= 720 && avctx->height <= 608) avctx->level = 5;
            else                                            avctx->level = 2;
        }else{
            if(avctx->profile != 1 && s->chroma_format != CHROMA_420){
                av_log(avctx, AV_LOG_ERROR, "Only High(1) and 4:2:2(0) profiles support 4:2:2 color sampling\n");
                return -1;
            }
            if(avctx->width <= 720 && avctx->height <= 576) avctx->level = 8;
            else if(avctx->width <= 1440)                   avctx->level = 6;
            else                                            avctx->level = 4;
        }
    }

    if((avctx->flags2 & CODEC_FLAG2_DROP_FRAME_TIMECODE) && s->frame_rate_index != 4){
        av_log(avctx, AV_LOG_ERROR, "Drop frame time code only allowed with 1001/30000 fps\n");
        return -1;
    }

    return 0;
}
