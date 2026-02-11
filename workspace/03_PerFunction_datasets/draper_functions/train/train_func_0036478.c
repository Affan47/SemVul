H5C_load_entry(H5F_t *             f,
               hid_t               dxpl_id,
               const H5C_class_t * type,
               haddr_t             addr,
               void *              udata)
{
    void *		thing = NULL;
    H5C_cache_entry_t *	entry;
    void *		ret_value;

    FUNC_ENTER_NOAPI_NOINIT

    HDassert(f);
    HDassert(f->shared);
    HDassert(f->shared->cache);
    HDassert(type);
    HDassert(type->load);
    HDassert(type->size);
    HDassert(H5F_addr_defined(addr));

    if(NULL == (thing = (type->load)(f, dxpl_id, addr, udata)))

        HGOTO_ERROR(H5E_CACHE, H5E_CANTLOAD, NULL, "unable to load entry")


    entry = (H5C_cache_entry_t *)thing;


    HDassert( ( entry->is_dirty == FALSE ) || ( type->id == 5 ) );
#ifndef NDEBUG
    entry->magic                = H5C__H5C_CACHE_ENTRY_T_MAGIC;
#endif
    entry->cache_ptr            = f->shared->cache;
    entry->addr                 = addr;
    entry->type                 = type;
    entry->is_protected         = FALSE;
    entry->is_read_only         = FALSE;
    entry->ro_ref_count         = 0;
    entry->in_slist             = FALSE;
    entry->flush_marker         = FALSE;
#ifdef H5_HAVE_PARALLEL
    entry->clear_on_unprotect   = FALSE;
    entry->flush_immediately    = FALSE;
#endif
    entry->flush_in_progress    = FALSE;
    entry->destroy_in_progress  = FALSE;
    entry->free_file_space_on_destroy = FALSE;

    if((type->size)(f, thing, &(entry->size)) < 0)

        HGOTO_ERROR(H5E_RESOURCE, H5E_CANTGETSIZE, NULL, "Can't get size of thing")

    HDassert( entry->size < H5C_MAX_ENTRY_SIZE );

    entry->next                 = NULL;
    entry->prev                 = NULL;

    entry->aux_next             = NULL;
    entry->aux_prev             = NULL;

    H5C__RESET_CACHE_ENTRY_STATS(entry);

    ret_value = thing;

done:

    FUNC_LEAVE_NOAPI(ret_value)
}
