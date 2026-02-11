H5G__has_links_test(hid_t gid, unsigned *nmsgs)
{
    H5G_t *grp = NULL;
    htri_t msg_exists = 0;
    hid_t dxpl_id = H5AC_ind_dxpl_id;
    htri_t ret_value = TRUE;

    FUNC_ENTER_PACKAGE


    if(NULL == (grp = (H5G_t *)H5I_object_verify(gid, H5I_GROUP)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a group")


    if((msg_exists = H5O_msg_exists(&(grp->oloc), H5O_LINK_ID, dxpl_id)) < 0)
	HGOTO_ERROR(H5E_SYM, H5E_CANTINIT, FAIL, "unable to read object header")
    if(msg_exists == 0)
        HGOTO_DONE(FALSE)


    if((msg_exists = H5O_msg_exists(&(grp->oloc), H5O_STAB_ID, dxpl_id)) < 0)
	HGOTO_ERROR(H5E_SYM, H5E_CANTINIT, FAIL, "unable to read object header")
    if(msg_exists > 0)
	HGOTO_ERROR(H5E_SYM, H5E_BADVALUE, FAIL, "both symbol table and link messages found")


    if(nmsgs) {
        int msg_count;


        if((msg_count = H5O_msg_count(&(grp->oloc), H5O_LINK_ID, dxpl_id)) < 0)
            HGOTO_ERROR(H5E_SYM, H5E_CANTCOUNT, FAIL, "unable to count link messages")
        *nmsgs = (unsigned)msg_count;
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
