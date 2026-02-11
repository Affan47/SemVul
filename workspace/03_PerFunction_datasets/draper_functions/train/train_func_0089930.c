H5O_dtype_encode(H5F_t *f, uint8_t *p, const void *mesg)
{
    const H5T_t	   *dt = (const H5T_t *) mesg;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5O_dtype_encode)


    HDassert(f);
    HDassert(p);
    HDassert(dt);


    if(H5O_dtype_encode_helper(f, &p, dt) < 0)
	HGOTO_ERROR(H5E_DATATYPE, H5E_CANTENCODE, FAIL, "can't encode type")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
