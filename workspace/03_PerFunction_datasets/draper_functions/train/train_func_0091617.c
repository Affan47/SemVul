load_func(mca_bcol_ptpcoll_module_t *ptpcoll_module)
{
    int fnc;


    for (fnc = 0; fnc < BCOL_NUM_OF_FUNCTIONS; fnc++) {


        ptpcoll_module->super.bcol_function_table[fnc] = NULL;
        ptpcoll_module->super.bcol_function_init_table[fnc] = NULL;
    }

    ptpcoll_module->super.bcol_function_init_table[BCOL_BARRIER] = bcol_ptpcoll_barrier_init;

    ptpcoll_module->super.bcol_function_init_table[BCOL_BCAST] = bcol_ptpcoll_bcast_init;
    ptpcoll_module->super.bcol_function_init_table[BCOL_ALLREDUCE] = NULL;
    ptpcoll_module->super.bcol_function_init_table[BCOL_ALLGATHER] = NULL;
    ptpcoll_module->super.bcol_function_table[BCOL_BCAST] = bcol_ptpcoll_bcast_k_nomial_anyroot;
    ptpcoll_module->super.bcol_function_init_table[BCOL_ALLTOALL] = NULL;
    ptpcoll_module->super.bcol_function_init_table[BCOL_SYNC] = mca_bcol_ptpcoll_memsync_init;


    ptpcoll_module->super.bcol_memory_init = mca_bcol_ptpcoll_cache_ml_memory_info;


    ptpcoll_module->super.set_small_msg_thresholds = mca_bcol_ptpcoll_set_small_msg_thresholds;


    ptpcoll_module->super.k_nomial_tree = mca_bcol_ptpcoll_setup_knomial_tree;
}
