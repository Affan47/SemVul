H5T_close(H5T_t *dt)
{
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)

    HDassert(dt && dt->shared);

    if(dt->shared->state == H5T_STATE_OPEN)
        dt->shared->fo_count--;

    if(dt->shared->state != H5T_STATE_OPEN || dt->shared->fo_count == 0) {
        if(H5T__free(dt) < 0)
            HGOTO_ERROR(H5E_DATATYPE, H5E_CANTFREE, FAIL, "unable to free datatype");

        dt->shared = H5FL_FREE(H5T_shared_t, dt->shared);
    } else {


        if(H5T_STATE_OPEN == dt->shared->state) {
            HDassert(dt->sh_loc.type == H5O_SHARE_TYPE_COMMITTED);


            if(H5FO_top_decr(dt->sh_loc.file, dt->sh_loc.u.loc.oh_addr) < 0)
                HGOTO_ERROR(H5E_DATATYPE, H5E_CANTRELEASE, FAIL, "can't decrement count for object")


            if(H5FO_top_count(dt->sh_loc.file, dt->sh_loc.u.loc.oh_addr) == 0) {

                if(H5O_close(&dt->oloc) < 0)
                    HGOTO_ERROR(H5E_DATATYPE, H5E_CANTINIT, FAIL, "unable to close")
            }
            else


                if(H5O_loc_free(&(dt->oloc)) < 0)
                    HGOTO_ERROR(H5E_DATATYPE, H5E_CANTRELEASE, FAIL, "problem attempting to free location")
        }


        H5G_name_free(&(dt->path));
    }


    dt = H5FL_FREE(H5T_t, dt);

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
