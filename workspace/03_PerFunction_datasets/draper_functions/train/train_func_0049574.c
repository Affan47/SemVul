flute_all_free(flute_all_susp_type susp)
{

	    deleteInstrument(susp->myflute);
    sound_unref(susp->breath_env);
    sound_unref(susp->freq_env);
    sound_unref(susp->jet_delay);
    sound_unref(susp->noise);
    ffree_generic(susp, sizeof(flute_all_susp_node), "flute_all_free");
}
