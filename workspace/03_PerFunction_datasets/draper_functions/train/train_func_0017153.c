_shmem_finalize(void)
{
    int ret = OSHMEM_SUCCESS;

    shmem_barrier_all();

    shmem_lock_finalize();


    if (OSHMEM_SUCCESS != (ret = oshmem_shmem_preconnect_all_finalize())) {
        return ret;
    }


    if (OSHMEM_SUCCESS != (ret = oshmem_request_finalize())) {
        return ret;
    }

    if (OSHMEM_SUCCESS != (ret = oshmem_group_cache_list_free())) {
        return ret;
    }

    mca_scoll_base_group_unselect(oshmem_group_all);


    if (OSHMEM_SUCCESS != (ret = mca_base_framework_close(&oshmem_atomic_base_framework) ) ) {
        return ret;
    }

    if (OSHMEM_SUCCESS != (ret = mca_base_framework_close(&oshmem_scoll_base_framework) ) ) {
        return ret;
    }

    if (OSHMEM_SUCCESS != (ret = mca_base_framework_close(&oshmem_memheap_base_framework) ) ) {
        return ret;
    }

    if (OSHMEM_SUCCESS
            != (ret =
                    MCA_SPML_CALL(del_procs(oshmem_group_all->proc_array, oshmem_group_all->proc_count)))) {
        return ret;
    }


    if (OSHMEM_SUCCESS != (ret = mca_spml_base_finalize())) {
        return ret;
    }

    if (OSHMEM_SUCCESS != (ret = mca_base_framework_close(&oshmem_spml_base_framework) ) ) {
        return ret;
    }


    if (OSHMEM_SUCCESS != (ret = oshmem_op_finalize())) {
        return ret;
    }


    if (OSHMEM_SUCCESS != (ret = oshmem_proc_finalize())) {
        return ret;
    }

    return ret;
}
