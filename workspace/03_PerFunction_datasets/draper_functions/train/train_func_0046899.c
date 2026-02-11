H5P_is_fill_value_defined(const H5O_fill_t *fill, H5D_fill_value_t *status)
{
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)

    HDassert(fill);
    HDassert(status);


    if(fill->size == -1 && !fill->buf)
	*status = H5D_FILL_VALUE_UNDEFINED;

    else if(fill->size == 0 && !fill->buf)
	*status = H5D_FILL_VALUE_DEFAULT;

    else if(fill->size > 0 && fill->buf)
	*status = H5D_FILL_VALUE_USER_DEFINED;
    else {
	*status = H5D_FILL_VALUE_ERROR;
        HGOTO_ERROR(H5E_PLIST, H5E_BADRANGE, FAIL, "invalid combination of fill-value info")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
