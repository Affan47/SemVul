H5D__mark(const H5D_t *dataset, hid_t H5_ATTR_UNUSED dxpl_id, unsigned flags)
{
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_PACKAGE_NOERR


    HDassert(dataset);
    HDassert(!(flags & (unsigned)~(H5D_MARK_SPACE | H5D_MARK_LAYOUT)));


    if(flags & H5D_MARK_SPACE)
        dataset->shared->space_dirty = TRUE;
    if(flags & H5D_MARK_LAYOUT)
        dataset->shared->layout_dirty = TRUE;

    FUNC_LEAVE_NOAPI(ret_value)
}
