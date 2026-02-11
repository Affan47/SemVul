H5FS_sect_debug(const H5FS_t *fspace, const H5FS_section_info_t *sect, FILE *stream, int indent, int fwidth)
{
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(H5FS_sect_debug, FAIL)


    HDassert(fspace);
    HDassert(sect);
    HDassert(stream);
    HDassert(indent >= 0);
    HDassert(fwidth >= 0);


    if(fspace->sect_cls[sect->type].debug)
        if((fspace->sect_cls[sect->type].debug)(sect, stream, indent, fwidth) < 0)
            HGOTO_ERROR(H5E_FSPACE, H5E_BADITER, FAIL, "can't dump section's debugging info")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
