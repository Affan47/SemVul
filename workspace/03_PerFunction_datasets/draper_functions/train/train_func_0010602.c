H5E_create_msg(H5E_cls_t *cls, H5E_type_t msg_type, const char *msg_str)
{
    H5E_msg_t   *msg = NULL;
    H5E_msg_t   *ret_value;

    FUNC_ENTER_NOAPI_NOINIT(H5E_create_msg)


    HDassert(cls);
    HDassert(msg_type == H5E_MAJOR || msg_type == H5E_MINOR);
    HDassert(msg_str);


    if(NULL == (msg = H5FL_MALLOC(H5E_msg_t)))
        HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, NULL, "memory allocation failed")


    msg->cls = cls;
    msg->type = msg_type;
    if(NULL == (msg->msg = H5MM_xstrdup(msg_str)))
        HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, NULL, "memory allocation failed")


    ret_value = msg;

done:
    if(!ret_value)
        if(msg && H5E_close_msg(msg) < 0)
            HDONE_ERROR(H5E_ERROR, H5E_CANTCLOSEOBJ, NULL, "unable to close error message")

    FUNC_LEAVE_NOAPI(ret_value)
}
