H5F_sfile_add(H5F_file_t *shared)
{
    H5F_sfile_node_t *new_shared;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5F_sfile_add)


    HDassert(shared);


    if (NULL == (new_shared = H5FL_CALLOC(H5F_sfile_node_t)))
	HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, FAIL, "memory allocation failed")


    new_shared->shared = shared;


    new_shared->next = H5F_sfile_head_g;
    H5F_sfile_head_g = new_shared;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
