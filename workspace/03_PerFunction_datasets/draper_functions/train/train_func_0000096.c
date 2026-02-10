flute_freq_free(flute_freq_susp_type susp)
{

	    deleteInstrument(susp->myflute);
    sound_unref(susp->breath_env);
    sound_unref(susp->freq_env);
    ffree_generic(susp, sizeof(flute_freq_susp_node), "flute_freq_free");
}
