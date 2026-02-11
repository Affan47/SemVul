H5Lunpack_elink_val(const void *_ext_linkval, size_t link_size,
    unsigned *flags, const char **filename, const char **obj_path)
{
    const uint8_t *ext_linkval = (const uint8_t *)_ext_linkval;
    unsigned    lnk_version;
    unsigned    lnk_flags;
    size_t      len;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE5("e", "*xz*Iu**s**s", _ext_linkval, link_size, flags, filename,
             obj_path);


    if(ext_linkval == NULL )
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "not an external link linkval buffer")
    lnk_version = (*ext_linkval >> 4) & 0x0F;
    lnk_flags = *ext_linkval & 0x0F;
    if(lnk_version > H5L_EXT_VERSION)
        HGOTO_ERROR(H5E_LINK, H5E_CANTDECODE, FAIL, "bad version number for external link")
    if(lnk_flags & (unsigned)~H5L_EXT_FLAGS_ALL)
        HGOTO_ERROR(H5E_LINK, H5E_CANTDECODE, FAIL, "bad flags for external link")
    if(link_size <= 2)
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "not a valid external link buffer")


    if(ext_linkval[link_size - 1] != '\0')
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "linkval buffer is not NULL-terminated")


    len = HDstrlen((const char *)ext_linkval + 1);


    if((len + 1) >= (link_size - 1))
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "linkval buffer doesn't contain an object path")


    if(filename)
        *filename = (const char *)ext_linkval + 1;
    if(obj_path)
        *obj_path = ((const char *)ext_linkval + 1) + len + 1;


    if(flags)
        *flags = lnk_flags;

done:
    FUNC_LEAVE_API(ret_value)
}
