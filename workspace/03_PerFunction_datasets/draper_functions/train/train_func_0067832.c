_algorithm_f_central_counter(struct oshmem_group_t *group,
                                         void *target,
                                         const void *source,
                                         size_t nlong,
                                         long *pSync)
{
    int rc = OSHMEM_SUCCESS;
    int i = 0;
    int PE_root = oshmem_proc_pe(group->proc_array[0]);

    SCOLL_VERBOSE(12,
                  "[#%d] Collect algorithm: Central Counter (identical size)",
                  group->my_pe);
    SCOLL_VERBOSE(15, "[#%d] pSync[0] = %ld", group->my_pe, pSync[0]);

    if (PE_root == group->my_pe) {
        int pe_cur = 0;

        memcpy((void*) ((unsigned char*) target + 0 * nlong),
               (void *) source,
               nlong);

        SCOLL_VERBOSE(14,
                      "[#%d] Gather data from all PEs in the group",
                      group->my_pe);
        for (i = 0; (i < group->proc_count) && (rc == OSHMEM_SUCCESS); i++) {

            pe_cur = oshmem_proc_pe(group->proc_array[i]);

            if (pe_cur == group->my_pe)
                continue;

            SCOLL_VERBOSE(14,
                          "[#%d] Gather data (%d bytes) from #%d",
                          group->my_pe, (int)nlong, pe_cur);


            rc = MCA_SPML_CALL(get((void *)source, nlong, (void*)((unsigned char*)target + i * nlong), pe_cur));
        }
    }


    if (rc == OSHMEM_SUCCESS) {
        SCOLL_VERBOSE(14,
                      "[#%d] Broadcast from the root #%d",
                      group->my_pe, PE_root);
        rc = group->g_scoll.scoll_broadcast(group,
                                            PE_root,
                                            target,
                                            target,
                                            group->proc_count * nlong,
                                            (pSync + 1),
                                            SCOLL_DEFAULT_ALG);
    }

    SCOLL_VERBOSE(15, "[#%d] pSync[0] = %ld", group->my_pe, pSync[0]);

    return rc;
}
