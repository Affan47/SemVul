mca_pml_base_bsend_fini(void)
{
    if(OPAL_THREAD_ADD32(&mca_pml_bsend_init,-1) > 0)
        return OMPI_SUCCESS;

    if(NULL != mca_pml_bsend_allocator)
        mca_pml_bsend_allocator->alc_finalize(mca_pml_bsend_allocator);
    mca_pml_bsend_allocator = NULL;

    OBJ_DESTRUCT(&mca_pml_bsend_condition);
    OBJ_DESTRUCT(&mca_pml_bsend_mutex);
    return OMPI_SUCCESS;
}
