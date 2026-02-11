allpoles_free(allpoles_susp_type susp)
{

     free(susp->zk_buf);
     free(susp->ak_coefs);
     susp->ak_array = NULL;
    sound_unref(susp->x_snd);
    ffree_generic(susp, sizeof(allpoles_susp_node), "allpoles_free");
}
