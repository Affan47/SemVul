H5G__is_new_dense_test(hid_t gid)
{
    H5G_t *grp = NULL;
    htri_t msg_exists = 0;
    htri_t ret_value = TRUE;

    FUNC_ENTER_PACKAGE


    if(NULL == (grp = (H5G_t *)H5I_object_verify(gid, H5I_GROUP)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a group")


    if((msg_exists = H5O_msg_exists(&(grp->oloc), H5O_STAB_ID, H5AC_dxpl_id)) < 0)
	HGOTO_ERROR(H5E_SYM, H5E_CANTINIT, FAIL, "unable to read object header")
    if(msg_exists > 0)
        HGOTO_DONE(FALSE)


    if((msg_exists = H5O_msg_exists(&(grp->oloc), H5O_LINK_ID, H5AC_dxpl_id)) < 0)
	HGOTO_ERROR(H5E_SYM, H5E_CANTINIT, FAIL, "unable to read object header")
    if(msg_exists > 0)
        HGOTO_DONE(FALSE)


    if((msg_exists = H5O_msg_exists(&(grp->oloc), H5O_LINFO_ID, H5AC_dxpl_id)) < 0)
	HGOTO_ERROR(H5E_SYM, H5E_CANTINIT, FAIL, "unable to read object header")
    if(msg_exists > 0) {
        H5O_linfo_t linfo;


        if(H5G__obj_get_linfo(&(grp->oloc), &linfo, H5AC_dxpl_id) < 0)
            HGOTO_ERROR(H5E_SYM, H5E_BADMESG, FAIL, "can't get link info")


        if(!H5F_addr_defined(linfo.fheap_addr))
            HGOTO_DONE(FALSE)
        if(!H5F_addr_defined(linfo.name_bt2_addr))
            HGOTO_DONE(FALSE)
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
