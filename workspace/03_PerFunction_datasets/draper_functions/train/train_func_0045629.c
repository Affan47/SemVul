Analysis_FastaPipe_Pair_query_func(FastaDB_Seq *fdbs,
                                                   gpointer user_data){
    register Analysis *analysis = user_data;
    g_assert(!analysis->curr_query);


    if(analysis->verbosity > 1)
        g_message("Load query for pairwise comparision [%s] (%d)",
                  fdbs->seq->id, fdbs->seq->len);
    analysis->curr_query = FastaDB_Seq_share(fdbs);
    return TRUE;
    }
