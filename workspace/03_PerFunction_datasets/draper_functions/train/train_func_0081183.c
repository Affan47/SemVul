H5MM_xstrdup(const char *s)
{
    char	*ret_value = NULL;


    FUNC_ENTER_NOAPI_NOINIT_NOFUNC(H5MM_xstrdup)

    if(s) {
        ret_value = (char *)H5MM_malloc(HDstrlen(s) + 1);
        HDassert(ret_value);
        HDstrcpy(ret_value, s);
    }

    FUNC_LEAVE_NOAPI(ret_value)
}
