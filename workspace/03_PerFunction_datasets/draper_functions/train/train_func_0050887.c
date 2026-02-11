H5MF_alloc_open(H5F_t *f, hid_t dxpl_id, H5FD_mem_t type)
{
    const H5FS_section_class_t *classes[] = {
        H5MF_FSPACE_SECT_CLS_SIMPLE};
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(f);
    HDassert(f->shared);
    HDassert(type != H5FD_MEM_NOLIST);
    HDassert(H5F_addr_defined(f->shared->fs_addr[type]));
    HDassert(f->shared->fs_state[type] == H5F_FS_STATE_CLOSED);


    if(NULL == (f->shared->fs_man[type] = H5FS_open(f, dxpl_id, f->shared->fs_addr[type],
	    NELMTS(classes), classes, f, f->shared->alignment, f->shared->threshold)))
	HGOTO_ERROR(H5E_RESOURCE, H5E_CANTINIT, FAIL, "can't initialize free space info")


    if(f->shared->fs_man[type])
        f->shared->fs_state[type] = H5F_FS_STATE_OPEN;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
