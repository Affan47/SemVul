H5G__stab_create_components(H5F_t *f, H5O_stab_t *stab, size_t size_hint, hid_t dxpl_id)
{
    H5HL_t *heap = NULL;
    size_t name_offset;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_PACKAGE


    HDassert(f);
    HDassert(stab);
    HDassert(size_hint > 0);


    if(H5B_create(f, dxpl_id, H5B_SNODE, NULL, &(stab->btree_addr)) < 0)
	HGOTO_ERROR(H5E_SYM, H5E_CANTINIT, FAIL, "can't create B-tree")


    if(H5HL_create(f, dxpl_id, size_hint, &(stab->heap_addr)) < 0)
	HGOTO_ERROR(H5E_SYM, H5E_CANTINIT, FAIL, "can't create heap")


    if(NULL == (heap = H5HL_protect(f, dxpl_id, stab->heap_addr, H5AC_WRITE)))
        HGOTO_ERROR(H5E_SYM, H5E_PROTECT, FAIL, "unable to protect symbol table heap")


    if((size_t)(-1) == (name_offset = H5HL_insert(f, dxpl_id, heap, (size_t)1, "")))
	HGOTO_ERROR(H5E_SYM, H5E_CANTINSERT, FAIL, "can't insert name into heap")


    HDassert(0 == name_offset);

done:

    if(heap && H5HL_unprotect(heap) < 0)
        HDONE_ERROR(H5E_SYM, H5E_PROTECT, FAIL, "unable to unprotect symbol table heap")

    FUNC_LEAVE_NOAPI(ret_value)
}
