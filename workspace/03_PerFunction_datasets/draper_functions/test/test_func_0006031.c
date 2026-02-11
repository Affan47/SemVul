decode_header_trees(SmackVContext *smk) {
    GetBitContext gb;
    int mmap_size, mclr_size, full_size, type_size;

    mmap_size = AV_RL32(smk->avctx->extradata);
    mclr_size = AV_RL32(smk->avctx->extradata + 4);
    full_size = AV_RL32(smk->avctx->extradata + 8);
    type_size = AV_RL32(smk->avctx->extradata + 12);

    init_get_bits(&gb, smk->avctx->extradata + 16, (smk->avctx->extradata_size - 16) * 8);

    if(!get_bits1(&gb)) {
        av_log(smk->avctx, AV_LOG_INFO, "Skipping MMAP tree\n");
        smk->mmap_tbl = av_malloc(sizeof(int) * 2);
        smk->mmap_tbl[0] = 0;
        smk->mmap_last[0] = smk->mmap_last[1] = smk->mmap_last[2] = 1;
    } else {
        smacker_decode_header_tree(smk, &gb, &smk->mmap_tbl, smk->mmap_last, mmap_size);
    }
    if(!get_bits1(&gb)) {
        av_log(smk->avctx, AV_LOG_INFO, "Skipping MCLR tree\n");
        smk->mclr_tbl = av_malloc(sizeof(int) * 2);
        smk->mclr_tbl[0] = 0;
        smk->mclr_last[0] = smk->mclr_last[1] = smk->mclr_last[2] = 1;
    } else {
        smacker_decode_header_tree(smk, &gb, &smk->mclr_tbl, smk->mclr_last, mclr_size);
    }
    if(!get_bits1(&gb)) {
        av_log(smk->avctx, AV_LOG_INFO, "Skipping FULL tree\n");
        smk->full_tbl = av_malloc(sizeof(int) * 2);
        smk->full_tbl[0] = 0;
        smk->full_last[0] = smk->full_last[1] = smk->full_last[2] = 1;
    } else {
        smacker_decode_header_tree(smk, &gb, &smk->full_tbl, smk->full_last, full_size);
    }
    if(!get_bits1(&gb)) {
        av_log(smk->avctx, AV_LOG_INFO, "Skipping TYPE tree\n");
        smk->type_tbl = av_malloc(sizeof(int) * 2);
        smk->type_tbl[0] = 0;
        smk->type_last[0] = smk->type_last[1] = smk->type_last[2] = 1;
    } else {
        smacker_decode_header_tree(smk, &gb, &smk->type_tbl, smk->type_last, type_size);
    }

    return 0;
}
