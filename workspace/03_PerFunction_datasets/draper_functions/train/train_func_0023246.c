H5RS_dup_str(const char *s)
{
    char *new_str;
    size_t path_len;
    H5RS_str_t *ret_value;

    FUNC_ENTER_NOAPI(NULL)


    HDassert(s);


    path_len = HDstrlen(s);


    if(NULL == (new_str = (char *)H5FL_BLK_MALLOC(str_buf, path_len + 1)))
        HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, NULL, "memory allocation failed")


    HDstrncpy(new_str, s, (path_len + 1));


    ret_value = H5RS_own(new_str);

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
