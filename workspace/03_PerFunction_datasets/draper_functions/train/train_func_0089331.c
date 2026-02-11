H5G_dense_build_table_cb(const H5O_link_t *lnk, void *_udata)
{
    H5G_dense_bt_ud_t *udata = (H5G_dense_bt_ud_t *)_udata;
    herr_t ret_value = H5_ITER_CONT;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(lnk);
    HDassert(udata);
    HDassert(udata->curr_lnk < udata->ltable->nlinks);


    if(H5O_msg_copy(H5O_LINK_ID, lnk, &(udata->ltable->lnks[udata->curr_lnk])) == NULL)
        HGOTO_ERROR(H5E_SYM, H5E_CANTCOPY, H5_ITER_ERROR, "can't copy link message")


    udata->curr_lnk++;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
