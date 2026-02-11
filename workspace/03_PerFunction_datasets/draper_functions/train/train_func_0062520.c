H5Pset_vlen_mem_manager(hid_t plist_id, H5MM_allocate_t alloc_func,
    void *alloc_info, H5MM_free_t free_func, void *free_info)
{
    H5P_genplist_t *plist;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE5("e", "ix*xx*x", plist_id, alloc_func, alloc_info, free_func,
             free_info);


    if(NULL == (plist = H5P_object_verify(plist_id, H5P_DATASET_XFER)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a dataset transfer property list")


    if(H5P_set_vlen_mem_manager(plist, alloc_func, alloc_info, free_func, free_info) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTSET, FAIL, "unable to set values")

done:
    FUNC_LEAVE_API(ret_value)
}
