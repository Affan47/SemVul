snd_make_follow(sound_type sndin, double floor, double risetime, double falltime, long lookahead)
{
    register follow_susp_type susp;
    rate_type sr = sndin->sr;
    time_type t0 = sndin->t0;
    int interp_desc = 0;
    sample_type scale_factor = 1.0F;
    time_type t0_min = t0;
    falloc_generic(susp, follow_susp_node, "snd_make_follow");
    susp->lookahead = lookahead = lookahead + 1;
    susp->delaybuf = create_buf(floor, lookahead);
    susp->delayptr = susp->delaybuf;
    susp->prevptr = susp->delaybuf + lookahead - 1;
    *(susp->prevptr) = (sample_type) floor;;
    susp->endptr = susp->delaybuf + lookahead;
    susp->floor = floor; floor = log(floor);;
    susp->rise_factor = exp(- floor / (sndin->sr * risetime + 0.5));
    susp->fall_factor = exp(floor / (sndin->sr * falltime + 0.5));
    susp->value = susp->floor;
    susp->susp.fetch = follow_s_fetch;
    susp->terminate_cnt = UNKNOWN;

    if (t0 < sndin->t0) sound_prepend_zeros(sndin, t0);

    t0_min = min(sndin->t0, t0);

    susp->susp.toss_cnt = (long) ((t0 - t0_min) * sr + 0.5);
    if (susp->susp.toss_cnt > 0) {
	susp->susp.keep_fetch = susp->susp.fetch;
	susp->susp.fetch = follow_toss_fetch;
    }


    susp->susp.free = follow_free;
    susp->susp.sr = sr;
    susp->susp.t0 = t0;
    susp->susp.mark = follow_mark;
    susp->susp.print_tree = follow_print_tree;
    susp->susp.name = "follow";
    susp->susp.log_stop_cnt = UNKNOWN;
    susp->susp.current = 0;
    susp->sndin = sndin;
    susp->sndin_cnt = 0;
    return sound_create((snd_susp_type)susp, t0, sr, scale_factor);
}
