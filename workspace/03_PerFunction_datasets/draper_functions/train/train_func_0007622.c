H5ST_find(H5ST_tree_t *tree, const char *s)
{
    H5ST_ptr_t ret_value;

    FUNC_ENTER_NOAPI(H5ST_find, NULL)

    if(NULL == (ret_value = H5ST_find_internal(tree->root, s)))
        HGOTO_ERROR(H5E_TST, H5E_NOTFOUND, NULL, "key not found in TST")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
