H5Dget_storage_size(hid_t dset_id)
{
    H5D_t	*dset;
    hsize_t	ret_value;

    FUNC_ENTER_API(0)
    H5TRACE1("h", "i", dset_id);


    if(NULL == (dset = (H5D_t *)H5I_object_verify(dset_id, H5I_DATASET)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, 0, "not a dataset")


    if(H5D__get_storage_size(dset, H5AC_ind_dxpl_id, &ret_value) < 0)
        HGOTO_ERROR(H5E_DATASET, H5E_CANTGET, 0, "can't get size of dataset's storage")

done:
    FUNC_LEAVE_API(ret_value)
}
