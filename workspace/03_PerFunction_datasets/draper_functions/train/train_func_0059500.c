Viterbi_Checkpoint_destroy(Viterbi_Checkpoint *vc){
    register gint i;
    for(i = 0; i < vc->checkpoint_list->len; i++)
        g_free(vc->checkpoint_list->pdata[i]);
    g_ptr_array_free(vc->checkpoint_list, TRUE);
    g_free(vc);
    return;
    }
