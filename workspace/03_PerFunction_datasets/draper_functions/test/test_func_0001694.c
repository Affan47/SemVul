H5O_name_decode(H5F_t UNUSED *f, hid_t UNUSED dxpl_id, H5O_t UNUSED *open_oh,
    unsigned UNUSED mesg_flags, unsigned UNUSED *ioflags, const uint8_t *p)
{
    H5O_name_t          *mesg;
    void                *ret_value;

    FUNC_ENTER_NOAPI_NOINIT(H5O_name_decode)


    HDassert(f);
    HDassert(p);


    if(NULL == (mesg = (H5O_name_t *)H5MM_calloc(sizeof(H5O_name_t))) ||
            NULL == (mesg->s = (char *)H5MM_malloc(HDstrlen((const char *)p) + 1)))
	HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, NULL, "memory allocation failed")
    HDstrcpy(mesg->s, (const char *)p);


    ret_value = mesg;

done:
    if(NULL == ret_value) {
        if(mesg)
            mesg = (H5O_name_t *)H5MM_xfree(mesg);
    }

    FUNC_LEAVE_NOAPI(ret_value)
}
