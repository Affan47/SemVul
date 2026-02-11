snd_make_fromarraystream(time_type t0, rate_type sr, LVAL src)
{
    register fromarraystream_susp_type susp;


    sample_type scale_factor = 1.0F;
    falloc_generic(susp, fromarraystream_susp_node, "snd_make_fromarraystream");
    susp->index = 0;
    susp->length = 0;
    susp->array = NULL;
    susp->src = src;
    susp->samples = NULL;;
    susp->susp.fetch = fromarraystream__fetch;


    susp->susp.free = fromarraystream_free;
    susp->susp.sr = sr;
    susp->susp.t0 = t0;
    susp->susp.mark = fromarraystream_mark;
    susp->susp.print_tree = fromarraystream_print_tree;
    susp->susp.name = "fromarraystream";
    susp->susp.log_stop_cnt = UNKNOWN;
    susp->susp.current = 0;
    return sound_create((snd_susp_type)susp, t0, sr, scale_factor);
}
