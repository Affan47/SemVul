snd_make_sndseq(s1, closure)
  sound_type s1;
  LVAL closure;
{
    register sndseq_susp_type susp;

    sample_type scale_factor = 1.0F;
    sound_type result;

    xlprot1(closure);
    falloc_generic(susp, sndseq_susp_node, "snd_make_sndseq");

    if (s1->scale != 1.0) {

        s1 = snd_make_normalize(s1);
    }

    susp->susp.fetch = sndseq_fetch;

    susp->terminate_cnt = UNKNOWN;
    susp->terminate_bits = 0;
    susp->logical_stop_bits = 0;


    susp->susp.free = sndseq_free;
    susp->susp.sr = s1->sr;
    susp->susp.t0 = s1->t0;
    susp->susp.mark = sndseq_mark;
    susp->susp.print_tree = sndseq_print_tree;
    susp->susp.name = "sndseq";
    susp->logically_stopped = false;
    susp->susp.log_stop_cnt = s1->logical_stop_cnt;
    if (!(susp->susp.log_stop_cnt >= 0 || susp->susp.log_stop_cnt == UNKNOWN)) {
        xlerror("Behaviors in SEQ must appear in chronological order", closure);
    }
    susp->started = false;
    susp->susp.current = 0;
    susp->s1 = s1;
    susp->s1_cnt = 0;
    susp->s2 = NULL;
    susp->s2_cnt = 0;
    susp->s2_phase = 0.0;


    susp->closure = closure;
    result = sound_create((snd_susp_type)susp, susp->susp.t0, susp->susp.sr, scale_factor);
    xlpopn(1);
    return result;
}
