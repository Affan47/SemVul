common_end(SnowContext *s){
    int plane_index, level, orientation, i;

    av_freep(&s->spatial_dwt_buffer);
    av_freep(&s->spatial_idwt_buffer);

    s->m.me.temp= NULL;
    av_freep(&s->m.me.scratchpad);
    av_freep(&s->m.me.map);
    av_freep(&s->m.me.score_map);
    av_freep(&s->m.obmc_scratchpad);

    av_freep(&s->block);
    av_freep(&s->scratchbuf);

    for(i=0; i<MAX_REF_FRAMES; i++){
        av_freep(&s->ref_mvs[i]);
        av_freep(&s->ref_scores[i]);
        if(s->last_picture[i].data[0])
            s->avctx->release_buffer(s->avctx, &s->last_picture[i]);
    }

    for(plane_index=0; plane_index<3; plane_index++){
        for(level=s->spatial_decomposition_count-1; level>=0; level--){
            for(orientation=level ? 1 : 0; orientation<4; orientation++){
                SubBand *b= &s->plane[plane_index].band[level][orientation];

                av_freep(&b->x_coeff);
            }
        }
    }
}
