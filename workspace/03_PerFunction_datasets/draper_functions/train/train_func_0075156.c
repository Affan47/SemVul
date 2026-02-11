H5O_fill_reset_dyn(H5O_fill_t *fill)
{
    hid_t fill_type_id = -1;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)

    HDassert(fill);

    if(fill->buf) {
        if(fill->type && H5T_detect_class(fill->type, H5T_VLEN, FALSE) > 0) {
            H5T_t *fill_type;
            H5S_t *fill_space;


            if(NULL == (fill_type = H5T_copy(fill->type, H5T_COPY_TRANSIENT)))
                HGOTO_ERROR(H5E_OHDR, H5E_CANTINIT, FAIL, "unable to copy fill value datatype")
            if((fill_type_id = H5I_register(H5I_DATATYPE, fill_type, FALSE)) < 0) {
                H5T_close(fill_type);
                HGOTO_ERROR(H5E_OHDR, H5E_CANTREGISTER, FAIL, "unable to register fill value datatype")
            }


            if(NULL == (fill_space = H5S_create(H5S_SCALAR)))
                HGOTO_ERROR(H5E_OHDR, H5E_CANTCREATE, FAIL, "can't create scalar dataspace")


            if(H5D_vlen_reclaim(fill_type_id, fill_space, H5P_DATASET_XFER_DEFAULT, fill->buf) < 0) {
                H5S_close(fill_space);
                HGOTO_ERROR(H5E_OHDR, H5E_BADITER, FAIL, "unable to reclaim variable-length fill value data")
            }


            H5S_close(fill_space);
        }


        fill->buf = H5MM_xfree(fill->buf);
    }
    fill->size = 0;
    if(fill->type) {
	H5T_close(fill->type);
	fill->type = NULL;
    }

done:
    if(fill_type_id > 0 && H5I_dec_ref(fill_type_id) < 0)
        HDONE_ERROR(H5E_OHDR, H5E_CANTDEC, FAIL, "unable to decrement ref count for temp ID")

    FUNC_LEAVE_NOAPI(ret_value)
}
