H5D_btree_debug(H5F_t *f, hid_t dxpl_id, haddr_t addr, FILE * stream, int indent,
		 int fwidth, unsigned ndims)
{
    H5D_btree_dbg_t     udata;
    H5O_storage_chunk_t storage;
    hbool_t     shared_init = FALSE;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)


    HDmemset(&storage, 0, sizeof(storage));
    storage.idx_type = H5D_CHUNK_BTREE;


    if(H5D__btree_shared_create(f, &storage, ndims) < 0)
	HGOTO_ERROR(H5E_RESOURCE, H5E_CANTINIT, FAIL, "can't create wrapper for shared B-tree info")
    shared_init = TRUE;


    udata.common.layout = NULL;
    udata.common.storage = &storage;
    udata.common.offset = NULL;
    udata.ndims = ndims;


    (void)H5B_debug(f, dxpl_id, addr, stream, indent, fwidth, H5B_BTREE, &udata);

done:
    if(shared_init) {

        if(NULL == storage.u.btree.shared)
            HDONE_ERROR(H5E_IO, H5E_CANTFREE, FAIL, "ref-counted page nil")
        else
            if(H5RC_DEC(storage.u.btree.shared) < 0)
                HDONE_ERROR(H5E_IO, H5E_CANTFREE, FAIL, "unable to decrement ref-counted page")
    }

    FUNC_LEAVE_NOAPI(ret_value)
}
