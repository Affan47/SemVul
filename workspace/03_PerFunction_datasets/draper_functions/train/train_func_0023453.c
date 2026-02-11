snd_make_modalbar(time_type t0, double freq, int preset, time_type dur, rate_type sr)
{
    register modalbar_susp_type susp;


    sample_type scale_factor = 1.0F;
    falloc_generic(susp, modalbar_susp_node, "snd_make_modalbar");
    susp->mymbar = initInstrument(MODALBAR, round(sr));
                  controlChange(susp->mymbar, 16, preset);;
    susp->temp_ret_value = noteOn(susp->mymbar, freq, 1.0);;
    susp->susp.fetch = modalbar__fetch;

    susp->terminate_cnt = round((dur) * sr);

    susp->susp.free = modalbar_free;
    susp->susp.sr = sr;
    susp->susp.t0 = t0;
    susp->susp.mark = NULL;
    susp->susp.print_tree = modalbar_print_tree;
    susp->susp.name = "modalbar";
    susp->susp.log_stop_cnt = UNKNOWN;
    susp->susp.current = 0;
    return sound_create((snd_susp_type)susp, t0, sr, scale_factor);
}
