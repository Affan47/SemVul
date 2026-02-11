expunge_entry(H5F_t * file_ptr,
              int32_t idx)
{
    const char * fcn_name = "expunge_entry()";
    hbool_t in_cache;
    herr_t result;
    struct datum * entry_ptr;

    HDassert( file_ptr );
    HDassert( ( 0 <= idx ) && ( idx < NUM_DATA_ENTRIES ) );
    HDassert( idx < virt_num_data_entries );

    entry_ptr = &(data[idx]);

    HDassert( !(entry_ptr->locked) );
    HDassert( !(entry_ptr->global_pinned) );
    HDassert( !(entry_ptr->local_pinned) );

    if ( nerrors == 0 ) {

        result = H5AC_expunge_entry(file_ptr, -1, &(types[0]),
			            entry_ptr->header.addr, H5AC__NO_FLAGS_SET);

        if ( result < 0 ) {

            nerrors++;
            if ( verbose ) {
	        HDfprintf(stdout, "%d:%s: Error in H5AC_expunge_entry().\n",
	                  world_mpi_rank, fcn_name);
            }
        }

        HDassert( ((entry_ptr->header).type)->id == DATUM_ENTRY_TYPE );
	HDassert( ! ((entry_ptr->header).is_dirty) );

	result = H5C_get_entry_status(file_ptr, entry_ptr->base_addr,
				      NULL, &in_cache, NULL, NULL, NULL);

	if ( result < 0 ) {

            nerrors++;
            if ( verbose ) {
	        HDfprintf(stdout, "%d:%s: Error in H5C_get_entry_status().\n",
	                  world_mpi_rank, fcn_name);
            }
        } else if ( in_cache ) {

            nerrors++;
            if ( verbose ) {
	        HDfprintf(stdout, "%d:%s: Expunged entry still in cache?!?\n",
	                  world_mpi_rank, fcn_name);
            }
        }
    }

    return;

}
