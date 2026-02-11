H5O_attr_remove(const H5O_loc_t *loc, const char *name, hid_t dxpl_id)
{
    H5O_t *oh = NULL;
    H5O_ainfo_t ainfo;
    htri_t ainfo_exists = FALSE;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(loc);
    HDassert(name);


    if(NULL == (oh = H5O_pin(loc, dxpl_id)))
	HGOTO_ERROR(H5E_ATTR, H5E_CANTPIN, FAIL, "unable to pin object header")


    ainfo.fheap_addr = HADDR_UNDEF;
    if(oh->version > H5O_VERSION_1) {

        if((ainfo_exists = H5A_get_ainfo(loc->file, dxpl_id, oh, &ainfo)) < 0)
            HGOTO_ERROR(H5E_ATTR, H5E_CANTGET, FAIL, "can't check for attribute info message")
    }


    if(H5F_addr_defined(ainfo.fheap_addr)) {

        if(H5A_dense_remove(loc->file, dxpl_id, &ainfo, name) < 0)
            HGOTO_ERROR(H5E_ATTR, H5E_CANTDELETE, FAIL, "unable to delete attribute in dense storage")
    }
    else {
        H5O_iter_rm_t udata;
        H5O_mesg_operator_t op;


        udata.f = loc->file;
        udata.dxpl_id = dxpl_id;
        udata.name = name;
        udata.found = FALSE;


        op.op_type = H5O_MESG_OP_LIB;
        op.u.lib_op = H5O_attr_remove_cb;
        if(H5O_msg_iterate_real(loc->file, oh, H5O_MSG_ATTR, &op, &udata, dxpl_id) < 0)
            HGOTO_ERROR(H5E_ATTR, H5E_CANTDELETE, FAIL, "error deleting attribute")


        if(!udata.found)
            HGOTO_ERROR(H5E_ATTR, H5E_NOTFOUND, FAIL, "can't locate attribute")
    }


    if(ainfo_exists)
        if(H5O_attr_remove_update(loc, oh, &ainfo, dxpl_id) < 0)
            HGOTO_ERROR(H5E_ATTR, H5E_CANTUPDATE, FAIL, "unable to update attribute info")


    if(H5O_touch_oh(loc->file, dxpl_id, oh, FALSE) < 0)
        HGOTO_ERROR(H5E_ATTR, H5E_CANTUPDATE, FAIL, "unable to update time on object")

done:
    if(oh && H5O_unpin(oh) < 0)
        HDONE_ERROR(H5E_ATTR, H5E_CANTUNPIN, FAIL, "unable to unpin object header")

    FUNC_LEAVE_NOAPI(ret_value)
}
