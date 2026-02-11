snd_make_siosc(LVAL lis, rate_type sr, double hz, time_type t0, sound_type s_fm)
{
    register siosc_susp_type susp;


    int interp_desc = 0;
    sample_type scale_factor = 1.0F;
    time_type t0_min = t0;
    falloc_generic(susp, siosc_susp_node, "snd_make_siosc");
    susp->table_len = 0.0;
    susp->ph_incr = 0.0;
    susp->table_a_ptr = NULL;
    susp->table_b_ptr_ptr = NULL;
    susp->table_a_samps = NULL;
    susp->table_b_samps = NULL;
    susp->table_sr = 0.0;
    susp->phase = 0.0;
    susp->lis = lis;
    susp->next_breakpoint = 0;
    susp->ampramp_a = 1.0;
    susp->ampramp_b = 0.0;
    susp->ampslope = 0.0;
    siosc_table_init(susp);
    susp->ph_incr = hz * susp->table_len / sr;
    s_fm->scale = (sample_type) (s_fm->scale * (susp->table_len / sr));


    interp_desc = (interp_desc << 2) + interp_style(s_fm, sr);
    switch (interp_desc) {
      case INTERP_n:
      case INTERP_s: susp->susp.fetch = siosc_s_fetch; break;
      case INTERP_i: susp->susp.fetch = siosc_i_fetch; break;
      case INTERP_r: susp->susp.fetch = siosc_r_fetch; break;
      default: snd_badsr(); break;
    }

    susp->terminate_cnt = UNKNOWN;

    if (t0 < s_fm->t0) sound_prepend_zeros(s_fm, t0);

    t0_min = min(s_fm->t0, t0);

    susp->susp.toss_cnt = (long) ((t0 - t0_min) * sr + 0.5);
    if (susp->susp.toss_cnt > 0) {
	susp->susp.keep_fetch = susp->susp.fetch;
	susp->susp.fetch = siosc_toss_fetch;
    }


    susp->susp.free = siosc_free;
    susp->susp.sr = sr;
    susp->susp.t0 = t0;
    susp->susp.mark = siosc_mark;
    susp->susp.print_tree = siosc_print_tree;
    susp->susp.name = "siosc";
    susp->logically_stopped = false;
    susp->susp.log_stop_cnt = logical_stop_cnt_cvt(s_fm);
    susp->started = false;
    susp->susp.current = 0;
    susp->s_fm = s_fm;
    susp->s_fm_cnt = 0;
    susp->s_fm_pHaSe = 0.0;
    susp->s_fm_pHaSe_iNcR = s_fm->sr / sr;
    susp->s_fm_n = 0;
    susp->output_per_s_fm = sr / s_fm->sr;
    return sound_create((snd_susp_type)susp, t0, sr, scale_factor);
}
