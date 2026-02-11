H5MM_strdup(const char *s)
{
    char	*ret_value;

    FUNC_ENTER_NOAPI(H5MM_strdup, NULL)

    if(!s)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, NULL, "null string")
    if(NULL == (ret_value = (char *)H5MM_malloc(HDstrlen(s) + 1)))
	HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, NULL, "memory allocation failed")
    HDstrcpy(ret_value, s);

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
