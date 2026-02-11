H5DOwrite_chunk(hid_t dset_id, hid_t dxpl_id, uint32_t filters, const hsize_t *offset,
         size_t data_size, const void *buf)
{
    hbool_t created_dxpl = FALSE;
    herr_t  ret_value = SUCCEED;

    if(dset_id < 0) {
        ret_value = FAIL;
        goto done;
    }

    if(!buf) {
        ret_value = FAIL;
        goto done;
    }

    if(!offset) {
        ret_value = FAIL;
        goto done;
    }

    if(!data_size) {
        ret_value = FAIL;
        goto done;
    }

    if(H5P_DEFAULT == dxpl_id) {
	if((dxpl_id = H5Pcreate(H5P_DATASET_XFER)) < 0) {
            ret_value = FAIL;
            goto done;
        }

        created_dxpl = TRUE;
    }

    if(H5DO_write_chunk(dset_id, dxpl_id, filters, offset, data_size, buf) < 0) {
        ret_value = FAIL;
        goto done;
    }

done:
    if(created_dxpl) {
        if(H5Pclose(dxpl_id) < 0)
            ret_value = FAIL;
    }

    return ret_value;
}
