snd_make_sax_all(double freq, sound_type breath_env, sound_type freq_env, double vibrato_freq, double vibrato_gain, sound_type reed_stiffness, sound_type noise, sound_type blow_pos, sound_type reed_table_offset, rate_type sr)
{
    register sax_all_susp_type susp;

    time_type t0 = breath_env->t0;
    int interp_desc = 0;
    sample_type scale_factor = 1.0F;
    time_type t0_min = t0;
    falloc_generic(susp, sax_all_susp_node, "snd_make_sax_all");
    susp->sax = initInstrument(SAXOFONY, round(sr));
    noteOn(susp->sax, freq, 1.0);
    controlChange(susp->sax, 29, SAX_CONTROL_CHANGE_CONST * vibrato_freq);
    controlChange(susp->sax, 1, SAX_CONTROL_CHANGE_CONST * vibrato_gain);;
    susp->frequency = freq;
    susp->susp.fetch = sax_all_ssssss_fetch;
    susp->terminate_cnt = UNKNOWN;

    if (t0 < breath_env->t0) sound_prepend_zeros(breath_env, t0);
    if (t0 < freq_env->t0) sound_prepend_zeros(freq_env, t0);
    if (t0 < reed_stiffness->t0) sound_prepend_zeros(reed_stiffness, t0);
    if (t0 < noise->t0) sound_prepend_zeros(noise, t0);
    if (t0 < blow_pos->t0) sound_prepend_zeros(blow_pos, t0);
    if (t0 < reed_table_offset->t0) sound_prepend_zeros(reed_table_offset, t0);

    t0_min = min(breath_env->t0, min(freq_env->t0, min(reed_stiffness->t0, min(noise->t0, min(blow_pos->t0, min(reed_table_offset->t0, t0))))));

    susp->susp.toss_cnt = (long) ((t0 - t0_min) * sr + 0.5);
    if (susp->susp.toss_cnt > 0) {
	susp->susp.keep_fetch = susp->susp.fetch;
	susp->susp.fetch = sax_all_toss_fetch;
    }


    susp->susp.free = sax_all_free;
    susp->susp.sr = sr;
    susp->susp.t0 = t0;
    susp->susp.mark = sax_all_mark;
    susp->susp.print_tree = sax_all_print_tree;
    susp->susp.name = "sax_all";
    susp->susp.log_stop_cnt = UNKNOWN;
    susp->susp.current = 0;
    susp->breath_env = breath_env;
    susp->breath_env_cnt = 0;
    susp->freq_env = freq_env;
    susp->freq_env_cnt = 0;
    susp->reed_stiffness = reed_stiffness;
    susp->reed_stiffness_cnt = 0;
    susp->noise = noise;
    susp->noise_cnt = 0;
    susp->blow_pos = blow_pos;
    susp->blow_pos_cnt = 0;
    susp->reed_table_offset = reed_table_offset;
    susp->reed_table_offset_cnt = 0;
    return sound_create((snd_susp_type)susp, t0, sr, scale_factor);
}
