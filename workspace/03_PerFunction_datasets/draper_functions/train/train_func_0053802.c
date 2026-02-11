H5C_load_entry(H5F_t *             f,
               hid_t               dxpl_id,
               const H5C_class_t * type,
               haddr_t             addr,
               void *              udata,
#ifndef NDEBUG
               hbool_t		   skip_file_checks)
#else
               hbool_t UNUSED	   skip_file_checks)
#endif
{
    void *		thing = NULL;
    void *		ret_value = NULL;
    H5C_cache_entry_t *	entry_ptr = NULL;

    FUNC_ENTER_NOAPI_NOINIT(H5C_load_entry)

    HDassert( f );
    HDassert( f->shared );
    HDassert( f->shared->cache );
    HDassert( skip_file_checks || f );
    HDassert( type );
    HDassert( type->load );
    HDassert( type->size );
    HDassert( H5F_addr_defined(addr) );

    if ( NULL == (thing = (type->load)(f, dxpl_id, addr, udata)) ) {

        HGOTO_ERROR(H5E_CACHE, H5E_CANTLOAD, NULL, "unable to load entry")

    }

    entry_ptr = (H5C_cache_entry_t *)thing;


    HDassert( ( entry_ptr->is_dirty == FALSE ) || ( type->id == 5 ) );
#ifndef NDEBUG
    entry_ptr->magic                = H5C__H5C_CACHE_ENTRY_T_MAGIC;
#endif
    entry_ptr->cache_ptr            = f->shared->cache;
    entry_ptr->addr                 = addr;
    entry_ptr->type                 = type;
    entry_ptr->is_protected         = FALSE;
    entry_ptr->is_read_only         = FALSE;
    entry_ptr->ro_ref_count         = 0;
    entry_ptr->in_slist             = FALSE;
    entry_ptr->flush_marker         = FALSE;
#ifdef H5_HAVE_PARALLEL
    entry_ptr->clear_on_unprotect   = FALSE;
#endif
    entry_ptr->flush_in_progress    = FALSE;
    entry_ptr->destroy_in_progress  = FALSE;
    entry_ptr->free_file_space_on_destroy = FALSE;

    if ( (type->size)(f, thing, &(entry_ptr->size)) < 0 ) {

        HGOTO_ERROR(H5E_RESOURCE, H5E_CANTGETSIZE, NULL, \
                    "Can't get size of thing")
    }

    HDassert( entry_ptr->size < H5C_MAX_ENTRY_SIZE );

    entry_ptr->ht_next = NULL;
    entry_ptr->ht_prev = NULL;

    entry_ptr->next                 = NULL;
    entry_ptr->prev                 = NULL;

    entry_ptr->aux_next             = NULL;
    entry_ptr->aux_prev             = NULL;

    H5C__RESET_CACHE_ENTRY_STATS(entry_ptr);

    ret_value = thing;

done:

    FUNC_LEAVE_NOAPI(ret_value)

}
