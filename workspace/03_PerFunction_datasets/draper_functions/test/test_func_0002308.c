mca_common_sm_local_proc_reorder(ompi_proc_t **procs,
                                 size_t num_procs,
                                 size_t *out_num_local_procs)
{
    size_t num_local_procs = 0;
    bool found_lowest = false;
    ompi_proc_t *temp_proc = NULL;
    size_t p;

    if (NULL == out_num_local_procs || NULL == procs) {
        return OMPI_ERR_BAD_PARAM;
    }


    for (p = 0; p < num_procs; ++p) {
        if (OPAL_PROC_ON_LOCAL_NODE(procs[p]->proc_flags)) {

            if (!found_lowest) {
                procs[0] = procs[p];
                found_lowest = true;
            }
            else {

                procs[num_local_procs] = procs[p];


                if (OPAL_VALUE2_GREATER ==
                    ompi_rte_compare_name_fields(OMPI_RTE_CMP_ALL,
                                                  &(procs[p]->proc_name),
                                                  &(procs[0]->proc_name))) {
                    temp_proc = procs[0];
                    procs[0] = procs[p];
                    procs[num_local_procs] = temp_proc;
                }
            }


            ++num_local_procs;
        }
    }
    *out_num_local_procs = num_local_procs;

    return OMPI_SUCCESS;
}
