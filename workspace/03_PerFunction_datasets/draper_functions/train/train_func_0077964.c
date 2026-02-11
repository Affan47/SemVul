H5G_compact_lookup_cb(const void *_mesg, unsigned UNUSED idx, void *_udata)
{
    const H5O_link_t *lnk = (const H5O_link_t *)_mesg;
    H5G_iter_lkp_t *udata = (H5G_iter_lkp_t *)_udata;
    herr_t ret_value = H5_ITER_CONT;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(lnk);
    HDassert(udata);


    if(HDstrcmp(lnk->name, udata->name) == 0) {
        if(udata->lnk) {

            if(NULL == H5O_msg_copy(H5O_LINK_ID, lnk, udata->lnk))
                HGOTO_ERROR(H5E_SYM, H5E_CANTCOPY, H5_ITER_ERROR, "can't copy link message")
        }


        udata->found = TRUE;


        HGOTO_DONE(H5_ITER_STOP)
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
