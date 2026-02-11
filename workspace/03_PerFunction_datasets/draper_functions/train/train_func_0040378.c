H5RS_xstrdup(const char *s)
{
    char *ret_value;

    FUNC_ENTER_NOAPI_NOINIT_NOERR

    if(s) {
        size_t len = HDstrlen(s) + 1;

        ret_value = (char *)H5FL_BLK_MALLOC(str_buf, len);
        HDassert(ret_value);
        HDstrncpy(ret_value, s, len);
    }
    else
        ret_value = NULL;

    FUNC_LEAVE_NOAPI(ret_value)
}
