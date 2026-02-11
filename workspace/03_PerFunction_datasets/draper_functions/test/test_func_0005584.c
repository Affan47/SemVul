mca_common_sm_fini(mca_common_sm_module_t *mca_common_sm_module)
{
    int rc = OMPI_SUCCESS;

    if (NULL != mca_common_sm_module->module_seg) {
        if (OPAL_SUCCESS !=
            opal_shmem_segment_detach(&mca_common_sm_module->shmem_ds)) {
            rc = OMPI_ERROR;
        }
    }
    return rc;
}
