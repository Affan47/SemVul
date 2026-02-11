H5SM_table_flush(H5F_t *f, hid_t dxpl_id, hbool_t destroy, haddr_t addr, H5SM_master_table_t *table)
{
    H5WB_t *wb = NULL;
    uint8_t tbl_buf[H5SM_TBL_BUF_SIZE];
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5SM_table_flush)


    HDassert(f);
    HDassert(H5F_addr_defined(addr));
    HDassert(table);

    if(table->cache_info.is_dirty) {
        uint8_t  *buf;
        uint8_t  *p;
        size_t	 size;
        uint32_t computed_chksum;
        size_t   x;


        HDassert(f->shared->sohm_vers == HDF5_SHAREDHEADER_VERSION);


        if(NULL == (wb = H5WB_wrap(tbl_buf, sizeof(tbl_buf))))
            HGOTO_ERROR(H5E_SOHM, H5E_CANTINIT, FAIL, "can't wrap buffer")


        size = H5SM_TABLE_SIZE(f) + (H5SM_INDEX_HEADER_SIZE(f) * table->num_indexes);


        if(NULL == (buf = (uint8_t *)H5WB_actual(wb, size)))
            HGOTO_ERROR(H5E_SOHM, H5E_NOSPACE, FAIL, "can't get actual buffer")


        p = buf;


        HDmemcpy(p, H5SM_TABLE_MAGIC, (size_t)H5_SIZEOF_MAGIC);
        p += H5_SIZEOF_MAGIC;


        for(x = 0; x < table->num_indexes; ++x) {

            *p++ = H5SM_LIST_VERSION;


            *p++ = table->indexes[x].index_type;


            UINT16ENCODE(p, table->indexes[x].mesg_types);


            UINT32ENCODE(p, table->indexes[x].min_mesg_size);


            UINT16ENCODE(p, table->indexes[x].list_max);


            UINT16ENCODE(p, table->indexes[x].btree_min);


            UINT16ENCODE(p, table->indexes[x].num_messages);


            H5F_addr_encode(f, &p, table->indexes[x].index_addr);


            H5F_addr_encode(f, &p, table->indexes[x].heap_addr);
        }


        computed_chksum = H5_checksum_metadata(buf, (size - H5SM_SIZEOF_CHECKSUM), 0);
        UINT32ENCODE(p, computed_chksum);


        HDassert((size_t)(p - buf) == size);
	if(H5F_block_write(f, H5FD_MEM_SOHM_TABLE, addr, size, dxpl_id, buf) < 0)
	    HGOTO_ERROR(H5E_SOHM, H5E_CANTFLUSH, FAIL, "unable to save sohm table to disk")

	table->cache_info.is_dirty = FALSE;
    }

    if(destroy)
        if(H5SM_table_dest(f, table) < 0)
	    HGOTO_ERROR(H5E_SOHM, H5E_CANTFREE, FAIL, "unable to destroy sohm table")

done:

    if(wb && H5WB_unwrap(wb) < 0)
        HDONE_ERROR(H5E_SOHM, H5E_CLOSEERROR, FAIL, "can't close wrapped buffer")

    FUNC_LEAVE_NOAPI(ret_value)
}
