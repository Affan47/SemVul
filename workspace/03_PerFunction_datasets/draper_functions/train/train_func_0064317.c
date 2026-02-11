load_func_with_choices(mca_bcol_base_module_t *super)
{
    int fnc;


    for (fnc=0; fnc < BCOL_NUM_OF_FUNCTIONS; fnc++) {
        super->bcol_function_init_table[fnc] = NULL;
    }

    super->bcol_function_init_table[BCOL_FANIN]  = bcol_basesmuma_fanin_init;
    super->bcol_function_init_table[BCOL_FANOUT] = bcol_basesmuma_fanout_init;
    super->bcol_function_init_table[BCOL_BARRIER] = bcol_basesmuma_barrier_init;

    super->bcol_function_init_table[BCOL_BCAST]  = bcol_basesmuma_bcast_init;
    super->bcol_function_init_table[BCOL_ALLREDUCE]  = bcol_basesmuma_allreduce_init;
    super->bcol_function_init_table[BCOL_REDUCE]  = bcol_basesmuma_reduce_init;
    super->bcol_function_init_table[BCOL_GATHER]  = bcol_basesmuma_gather_init;
    super->bcol_function_init_table[BCOL_ALLGATHER]  = bcol_basesmuma_allgather_init;
    super->bcol_function_init_table[BCOL_SYNC]  = bcol_basesmuma_memsync_init;

    super->bcol_memory_init                  = bcol_basesmuma_bank_init_opti;

    super->k_nomial_tree                     = bcol_basesmuma_setup_knomial_tree;

}
