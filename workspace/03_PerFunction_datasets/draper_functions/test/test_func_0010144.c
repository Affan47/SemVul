H5MF_sect_simple_new(haddr_t sect_off, hsize_t sect_size)
{
    H5MF_free_section_t *sect = NULL;
    H5MF_free_section_t *ret_value;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(sect_size);


    if(NULL == (sect = H5FL_MALLOC(H5MF_free_section_t)))
        HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, NULL, "memory allocation failed for direct block free list section")


    sect->sect_info.addr = sect_off;
    sect->sect_info.size = sect_size;


    sect->sect_info.type = H5MF_FSPACE_SECT_SIMPLE;
    sect->sect_info.state = H5FS_SECT_LIVE;


    ret_value = sect;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
