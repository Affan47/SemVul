H5AC_rsp__dist_md_write__flush_to_min_clean(H5F_t *f,
                                            hid_t dxpl_id,
                                            H5AC_t * cache_ptr)
{
    hbool_t 	 evictions_enabled;
    H5AC_aux_t * aux_ptr;
    herr_t	 ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)

    HDassert( f != NULL );
    HDassert( f->shared->cache == cache_ptr );

    HDassert( cache_ptr != NULL );
    HDassert( cache_ptr->magic == H5C__H5C_T_MAGIC );

    aux_ptr = (H5AC_aux_t *)(cache_ptr->aux_ptr);

    HDassert( aux_ptr != NULL );
    HDassert( aux_ptr->magic == H5AC__H5AC_AUX_T_MAGIC );
    HDassert( aux_ptr->metadata_write_strategy ==
              H5AC_METADATA_WRITE_STRATEGY__DISTRIBUTED );


    if(H5C_get_evictions_enabled((const H5C_t *)cache_ptr, &evictions_enabled) < 0)
        HGOTO_ERROR(H5E_CACHE, H5E_CANTGET, FAIL, "H5C_get_evictions_enabled() failed.")

    if(evictions_enabled) {

        if(aux_ptr->mpi_rank == 0) {
            if(H5AC_construct_candidate_list(cache_ptr, aux_ptr, H5AC_SYNC_POINT_OP__FLUSH_TO_MIN_CLEAN) < 0)
                HGOTO_ERROR(H5E_CACHE, H5E_CANTFLUSH, FAIL, "Can't construct candidate list.")
        }


        if(H5AC_propagate_and_apply_candidate_list(f, dxpl_id, cache_ptr) < 0)
            HGOTO_ERROR(H5E_CACHE, H5E_CANTFLUSH, FAIL, "Can't propagate and apply candidate list.")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
