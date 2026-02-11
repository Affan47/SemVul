H5RS_create(const char *s)
{
    H5RS_str_t *ret_value;

    FUNC_ENTER_NOAPI(NULL)


    if(NULL == (ret_value = H5FL_MALLOC(H5RS_str_t)))
        HGOTO_ERROR(H5E_RS, H5E_NOSPACE, NULL, "memory allocation failed")


    ret_value->s = H5RS_xstrdup(s);
    ret_value->wrapped = 0;
    ret_value->n = 1;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
