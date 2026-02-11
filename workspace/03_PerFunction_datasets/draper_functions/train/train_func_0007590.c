H5C_move_entry(H5C_t *	     cache_ptr,
                 const H5C_class_t * type,
                 haddr_t 	     old_addr,
	         haddr_t 	     new_addr)
{
    hbool_t			was_dirty;
    H5C_cache_entry_t *	entry_ptr = NULL;
    H5C_cache_entry_t *	test_entry_ptr = NULL;
#if H5C_DO_SANITY_CHECKS
    hbool_t			removed_entry_from_slist = FALSE;
#endif
    herr_t			ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)

    HDassert( cache_ptr );
    HDassert( cache_ptr->magic == H5C__H5C_T_MAGIC );
    HDassert( type );
    HDassert( H5F_addr_defined(old_addr) );
    HDassert( H5F_addr_defined(new_addr) );
    HDassert( H5F_addr_ne(old_addr, new_addr) );

#if H5C_DO_EXTREME_SANITY_CHECKS
        if ( H5C_validate_lru_list(cache_ptr) < 0 ) {

                HGOTO_ERROR(H5E_CACHE, H5E_SYSTEM, FAIL, \
                            "LRU sanity check failed.\n");
        }
#endif

    H5C__SEARCH_INDEX(cache_ptr, old_addr, entry_ptr, FAIL)

    if ( ( entry_ptr == NULL ) || ( entry_ptr->type != type ) ) {


        HGOTO_DONE(SUCCEED)
    }

    HDassert( entry_ptr->addr == old_addr );
    HDassert( entry_ptr->type == type );

    if ( entry_ptr->is_protected ) {

        HGOTO_ERROR(H5E_CACHE, H5E_CANTMOVE, FAIL, \
		    "Target entry is protected.")
    }

    H5C__SEARCH_INDEX(cache_ptr, new_addr, test_entry_ptr, FAIL)

    if ( test_entry_ptr != NULL ) {

        if ( test_entry_ptr->type == type ) {

            HGOTO_ERROR(H5E_CACHE, H5E_CANTMOVE, FAIL, \
                        "Target already moved & reinserted???.")

        } else {

            HGOTO_ERROR(H5E_CACHE, H5E_CANTMOVE, FAIL, \
                        "New address already in use?.")

        }
    }


    if ( ! ( entry_ptr->destroy_in_progress ) ) {

        H5C__DELETE_FROM_INDEX(cache_ptr, entry_ptr)

        if ( entry_ptr->in_slist ) {

            HDassert( cache_ptr->slist_ptr );

            H5C__REMOVE_ENTRY_FROM_SLIST(cache_ptr, entry_ptr)

#if H5C_DO_SANITY_CHECKS

            removed_entry_from_slist = TRUE;

#endif
        }
    }

    entry_ptr->addr = new_addr;

    if ( ! ( entry_ptr->destroy_in_progress ) ) {

        was_dirty = entry_ptr->is_dirty;

	if ( ! ( entry_ptr->flush_in_progress ) ) {

            entry_ptr->is_dirty = TRUE;
	}

        H5C__INSERT_IN_INDEX(cache_ptr, entry_ptr, FAIL)

	if ( ! ( entry_ptr->flush_in_progress ) ) {

            H5C__INSERT_ENTRY_IN_SLIST(cache_ptr, entry_ptr, FAIL)

#if H5C_DO_SANITY_CHECKS

            if ( removed_entry_from_slist ) {


		HDassert( cache_ptr->slist_len_increase > 1 );
		HDassert( cache_ptr->slist_size_increase > entry_ptr->size );

		cache_ptr->slist_len_increase -= 1;
		cache_ptr->slist_size_increase -= entry_ptr->size;
	    }

#endif

            H5C__UPDATE_RP_FOR_MOVE(cache_ptr, entry_ptr, was_dirty, FAIL)
	}
    }

    H5C__UPDATE_STATS_FOR_MOVE(cache_ptr, entry_ptr)

done:

#if H5C_DO_EXTREME_SANITY_CHECKS
        if ( H5C_validate_lru_list(cache_ptr) < 0 ) {

                HGOTO_ERROR(H5E_CACHE, H5E_SYSTEM, FAIL, \
                            "LRU sanity check failed.\n");
        }
#endif

    FUNC_LEAVE_NOAPI(ret_value)

}
