H5A_get_name(H5A_t *attr, size_t buf_size, char *buf)
{
    size_t              copy_len, nbytes;
    ssize_t		ret_value;

    FUNC_ENTER_NOAPI(H5A_get_name, FAIL)


    nbytes = HDstrlen(attr->shared->name);
    HDassert((ssize_t)nbytes >= 0);


    copy_len = MIN(buf_size - 1, nbytes);


    if(buf && copy_len > 0) {
        HDmemcpy(buf, attr->shared->name, copy_len);


        buf[copy_len]='\0';
    }


    ret_value = (ssize_t)nbytes;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
