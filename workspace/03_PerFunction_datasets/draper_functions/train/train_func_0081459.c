H5FD_family_fapl_free(void *_fa)
{
    H5FD_family_fapl_t	*fa = (H5FD_family_fapl_t*)_fa;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT

    if(H5I_dec_ref(fa->memb_fapl_id) < 0)
        HGOTO_ERROR(H5E_VFL, H5E_CANTDEC, FAIL, "can't close driver ID")
    H5MM_xfree(fa);

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
