snd_make_tone(sound_type input, double hz)
{
    register tone_susp_type susp;
    double b;
    rate_type sr = input->sr;
    time_type t0 = input->t0;
    int interp_desc = 0;
    sample_type scale_factor = 1.0F;
    time_type t0_min = t0;
    falloc_generic(susp, tone_susp_node, "snd_make_tone");
    b = 2.0 - cos(hz * PI2 / input->sr);
    susp->c2 = b - sqrt((b * b) - 1.0);
    susp->c1 = (1.0 - susp->c2) * input->scale;
    susp->prev = 0.0;
    susp->susp.fetch = tone_n_fetch;
    susp->terminate_cnt = UNKNOWN;

    if (t0 < input->t0) sound_prepend_zeros(input, t0);

    t0_min = min(input->t0, t0);

    susp->susp.toss_cnt = (long) ((t0 - t0_min) * sr + 0.5);
    if (susp->susp.toss_cnt > 0) {
	susp->susp.keep_fetch = susp->susp.fetch;
	susp->susp.fetch = tone_toss_fetch;
    }


    susp->susp.free = tone_free;
    susp->susp.sr = sr;
    susp->susp.t0 = t0;
    susp->susp.mark = tone_mark;
    susp->susp.print_tree = tone_print_tree;
    susp->susp.name = "tone";
    susp->logically_stopped = false;
    susp->susp.log_stop_cnt = logical_stop_cnt_cvt(input);
    susp->susp.current = 0;
    susp->input = input;
    susp->input_cnt = 0;
    return sound_create((snd_susp_type)susp, t0, sr, scale_factor);
}
