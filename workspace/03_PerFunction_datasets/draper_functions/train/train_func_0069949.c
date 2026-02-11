H5G_node_create(H5F_t *f, hid_t dxpl_id, H5B_ins_t UNUSED op, void *_lt_key,
		void UNUSED *_udata, void *_rt_key, haddr_t *addr_p)
{
    H5G_node_key_t	*lt_key = (H5G_node_key_t *)_lt_key;
    H5G_node_key_t	*rt_key = (H5G_node_key_t *)_rt_key;
    H5G_node_t		*sym = NULL;
    herr_t              ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5G_node_create)


    HDassert(f);
    HDassert(H5B_INS_FIRST == op);

    if(NULL == (sym = H5FL_CALLOC(H5G_node_t)))
	HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, FAIL, "memory allocation failed")
    sym->node_size = H5G_NODE_SIZE(f);
    if(HADDR_UNDEF == (*addr_p = H5MF_alloc(f, H5FD_MEM_BTREE, dxpl_id, (hsize_t)sym->node_size)))
	HGOTO_ERROR(H5E_SYM, H5E_CANTINIT, FAIL, "unable to allocate file space")
    if(NULL == (sym->entry = H5FL_SEQ_CALLOC(H5G_entry_t, (size_t)(2 * H5F_SYM_LEAF_K(f)))))
	HGOTO_ERROR(H5E_SYM, H5E_CANTALLOC, FAIL, "memory allocation failed")

    if(H5AC_insert_entry(f, dxpl_id, H5AC_SNODE, *addr_p, sym, H5AC__NO_FLAGS_SET) < 0)
	HGOTO_ERROR(H5E_SYM, H5E_CANTINIT, FAIL, "unable to cache symbol table leaf node")


    if(lt_key)
        lt_key->offset = 0;
    if(rt_key)
        rt_key->offset = 0;

done:
    if(ret_value < 0) {
        if(sym != NULL) {
            if(sym->entry != NULL)
                sym->entry = H5FL_SEQ_FREE(H5G_entry_t, sym->entry);
            sym = H5FL_FREE(H5G_node_t, sym);
        }
    }

    FUNC_LEAVE_NOAPI(ret_value)
}
