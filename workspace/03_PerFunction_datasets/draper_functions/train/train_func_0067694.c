lame_get_totalframes(const lame_global_flags * gfp)
{
    if (is_lame_global_flags_valid(gfp)) {
        lame_internal_flags const *const gfc = gfp->internal_flags;
        if (is_lame_internal_flags_valid(gfc)) {
            SessionConfig_t const *const cfg = &gfc->cfg;
            unsigned long const pcm_samples_per_frame = 576 * cfg->mode_gr;
            unsigned long pcm_samples_to_encode = gfp->num_samples;
            unsigned long end_padding = 0;


            if (pcm_samples_to_encode == (0ul-1ul)) {
                return 0;
            }
            if (gfp->samplerate_in != gfp->samplerate_out && gfp->samplerate_in > 0) {
                double const q = (double)gfp->samplerate_out / gfp->samplerate_in;
                pcm_samples_to_encode *= q;
            }
            pcm_samples_to_encode += 576;
            end_padding = pcm_samples_per_frame - (pcm_samples_to_encode % pcm_samples_per_frame);
            if (end_padding < 576) {
                end_padding += pcm_samples_per_frame;
            }
            pcm_samples_to_encode += end_padding;


            return pcm_samples_to_encode / pcm_samples_per_frame;
        }
    }
    return 0;
}
