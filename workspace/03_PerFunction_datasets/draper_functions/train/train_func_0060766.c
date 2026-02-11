H5D__layout_version_test(hid_t did, unsigned *version)
{
    H5D_t	*dset;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_PACKAGE


    if(NULL == (dset = (H5D_t *)H5I_object_verify(did, H5I_DATASET)))
        HGOTO_ERROR(H5E_DATASET, H5E_BADTYPE, FAIL, "not a dataset")

    if(version)
        *version = dset->shared->layout.version;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
