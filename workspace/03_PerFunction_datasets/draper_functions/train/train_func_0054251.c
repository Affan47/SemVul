H5G_dense_lookup_cb(const void *_lnk, void *_user_lnk)
{
    const H5O_link_t *lnk = (const H5O_link_t *)_lnk;
    H5O_link_t *user_lnk = (H5O_link_t *)_user_lnk;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5G_dense_lookup_cb)


    HDassert(lnk);
    HDassert(user_lnk);


    if(H5O_msg_copy(H5O_LINK_ID, lnk, user_lnk) == NULL)
        HGOTO_ERROR(H5E_SYM, H5E_CANTCOPY, H5_ITER_ERROR, "can't copy link message")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
