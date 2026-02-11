H5O_attr_open_by_idx(const H5O_loc_t *loc, H5_index_t idx_type,
    H5_iter_order_t order, hsize_t n, hid_t dxpl_id)
{
    H5O_t *oh = NULL;
    H5A_attr_iter_op_t attr_op;
    H5A_t *exist_attr = NULL;
    H5A_t *opened_attr = NULL;
    htri_t found_open_attr = FALSE;
    H5A_t *ret_value;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(loc);


    attr_op.op_type = H5A_ATTR_OP_LIB;
    attr_op.u.lib_op = H5O_attr_open_by_idx_cb;


    if(H5O_attr_iterate_real((hid_t)-1, loc, dxpl_id, idx_type, order, n, NULL, &attr_op, &opened_attr) < 0)
        HGOTO_ERROR(H5E_ATTR, H5E_BADITER, NULL, "can't locate attribute")


    if(NULL == (oh = H5O_protect(loc, dxpl_id, H5AC_READ)))
	HGOTO_ERROR(H5E_ATTR, H5E_CANTPROTECT, NULL, "unable to load object header")


    if(opened_attr) {
        if((found_open_attr = H5O_attr_find_opened_attr(loc, &exist_attr, opened_attr->shared->name)) < 0)
            HGOTO_ERROR(H5E_ATTR, H5E_CANTGET, NULL, "failed in finding opened attribute")


        if(found_open_attr && exist_attr) {
            if(H5A_close(opened_attr) < 0)
                HGOTO_ERROR(H5E_ATTR, H5E_CANTCLOSEOBJ, NULL, "can't close attribute")
            if(NULL == (opened_attr = H5A_copy(NULL, exist_attr)))
                HGOTO_ERROR(H5E_ATTR, H5E_CANTCOPY, NULL, "can't copy existing attribute")
        } else {

            if(H5T_set_loc(opened_attr->shared->dt, loc->file, H5T_LOC_DISK) < 0)
                HGOTO_ERROR(H5E_ATTR, H5E_CANTINIT, NULL, "invalid datatype location")
        }
    }


    ret_value = opened_attr;

done:
    if(oh && H5O_unprotect(loc, dxpl_id, oh, H5AC__NO_FLAGS_SET) < 0)
	HDONE_ERROR(H5E_ATTR, H5E_CANTUNPROTECT, NULL, "unable to release object header")


    if(NULL == ret_value && opened_attr)
        if(H5A_close(opened_attr) < 0)
            HDONE_ERROR(H5E_ATTR, H5E_CANTCLOSEOBJ, NULL, "can't close attribute")

    FUNC_LEAVE_NOAPI(ret_value)
}
