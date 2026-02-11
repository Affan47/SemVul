H5T_free(H5T_t *dt)
{
    unsigned	i;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(H5T_free, FAIL)

    HDassert(dt && dt->shared);


    if(H5T_STATE_OPEN == dt->shared->state) {
        HDassert(dt->sh_loc.type == H5O_SHARE_TYPE_COMMITTED);
        HDassert(H5F_addr_defined(dt->sh_loc.u.loc.oh_addr));
        HDassert(H5F_addr_defined(dt->oloc.addr));


        if(H5FO_top_decr(dt->sh_loc.file, dt->sh_loc.u.loc.oh_addr) < 0)
            HGOTO_ERROR(H5E_DATATYPE, H5E_CANTRELEASE, FAIL, "can't decrement count for object")
        if(H5FO_delete(dt->sh_loc.file, H5AC_dxpl_id, dt->sh_loc.u.loc.oh_addr) < 0)
            HGOTO_ERROR(H5E_DATATYPE, H5E_CANTRELEASE, FAIL, "can't remove datatype from list of open objects")
        if(H5O_close(&dt->oloc) < 0)
            HGOTO_ERROR(H5E_DATATYPE, H5E_CANTINIT, FAIL, "unable to close data type object header")
        dt->shared->state = H5T_STATE_NAMED;
    }


    H5G_name_free(&(dt->path));


    if(H5T_STATE_IMMUTABLE==dt->shared->state)
	HGOTO_ERROR(H5E_DATATYPE, H5E_CLOSEERROR, FAIL, "unable to close immutable datatype")


    switch(dt->shared->type) {
        case H5T_COMPOUND:
            for(i = 0; i < dt->shared->u.compnd.nmembs; i++) {
                H5MM_xfree(dt->shared->u.compnd.memb[i].name);
                H5T_close(dt->shared->u.compnd.memb[i].type);
            }
            H5MM_xfree(dt->shared->u.compnd.memb);
            break;

        case H5T_ENUM:
            for(i = 0; i < dt->shared->u.enumer.nmembs; i++)
                H5MM_xfree(dt->shared->u.enumer.name[i]);
            H5MM_xfree(dt->shared->u.enumer.name);
            H5MM_xfree(dt->shared->u.enumer.value);
            break;

        case H5T_OPAQUE:
            H5MM_xfree(dt->shared->u.opaque.tag);
            break;

        default:
            break;
    }


    HDassert(dt->shared->parent != dt);
    if(dt->shared->parent && H5T_close(dt->shared->parent) < 0)
	HGOTO_ERROR(H5E_DATATYPE, H5E_CANTCLOSEOBJ, FAIL, "unable to close parent data type")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
