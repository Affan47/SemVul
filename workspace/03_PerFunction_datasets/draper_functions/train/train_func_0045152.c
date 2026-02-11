lame_init_old(lame_global_flags * gfp)
{
    lame_internal_flags *gfc;

    disable_FPE();

    memset(gfp, 0, sizeof(lame_global_flags));

    gfp->class_id = LAME_ID;

    if (NULL == (gfc = gfp->internal_flags = calloc(1, sizeof(lame_internal_flags))))
        return -1;


    gfp->mode = NOT_SET;
    gfp->original = 1;
    gfp->in_samplerate = 44100;
    gfp->num_channels = 2;
    gfp->num_samples = MAX_U_32_NUM;

    gfp->bWriteVbrTag = 1;
    gfp->quality = -1;
    gfp->short_blocks = short_block_not_set;
    gfc->subblock_gain = -1;

    gfp->lowpassfreq = 0;
    gfp->highpassfreq = 0;
    gfp->lowpasswidth = -1;
    gfp->highpasswidth = -1;

    gfp->VBR = vbr_off;
    gfp->VBR_q = 4;
    gfp->ATHcurve = -1;
    gfp->VBR_mean_bitrate_kbps = 128;
    gfp->VBR_min_bitrate_kbps = 0;
    gfp->VBR_max_bitrate_kbps = 0;
    gfp->VBR_hard_min = 0;
    gfc->VBR_min_bitrate = 1;
    gfc->VBR_max_bitrate = 13;

    gfp->quant_comp = -1;
    gfp->quant_comp_short = -1;

    gfp->msfix = -1;

    gfc->resample_ratio = 1;

    gfc->OldValue[0] = 180;
    gfc->OldValue[1] = 180;
    gfc->CurrentStep[0] = 4;
    gfc->CurrentStep[1] = 4;
    gfc->masking_lower = 1;
    gfc->nsPsy.attackthre = -1;
    gfc->nsPsy.attackthre_s = -1;

    gfp->scale = -1;

    gfp->athaa_type = -1;
    gfp->ATHtype = -1;
    gfp->athaa_loudapprox = -1;

    gfp->athaa_sensitivity = 0.0;
    gfp->useTemporal = -1;
    gfp->interChRatio = -1;


    gfc->mf_samples_to_encode = ENCDELAY + POSTDELAY;
    gfp->encoder_padding = 0;
    gfc->mf_size = ENCDELAY - MDCTDELAY;

    gfp->findReplayGain = 0;
    gfp->decode_on_the_fly = 0;

    gfc->decode_on_the_fly = 0;
    gfc->findReplayGain = 0;
    gfc->findPeakSample = 0;

    gfc->RadioGain = 0;
    gfc->AudiophileGain = 0;
    gfc->noclipGainChange = 0;
    gfc->noclipScale = -1.0;

    gfp->asm_optimizations.mmx = 1;
    gfp->asm_optimizations.amd3dnow = 1;
    gfp->asm_optimizations.sse = 1;

    gfp->preset = 0;

    gfp->write_id3tag_automatic = 1;
    return 0;
}
