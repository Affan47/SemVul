H5DS_get_REFLIST_type(void)
{
    hid_t ntid_t = -1;


    if((ntid_t = H5Tcreate(H5T_COMPOUND, sizeof(ds_list_t))) < 0)
        goto out;

    if(H5Tinsert(ntid_t, "dataset", HOFFSET(ds_list_t,ref), H5T_STD_REF_OBJ) < 0)
        goto out;

    if(H5Tinsert(ntid_t, "dimension", HOFFSET(ds_list_t, dim_idx), H5T_NATIVE_INT) < 0)
        goto out;

    return ntid_t;
out:
    H5E_BEGIN_TRY {
        H5Tclose(ntid_t);
    } H5E_END_TRY;
    return FAIL;
}
