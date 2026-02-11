pin_entry(H5F_t * file_ptr,
          int32_t idx,
	  hbool_t global,
	  hbool_t dirty)
{

    unsigned int flags = H5AC__PIN_ENTRY_FLAG;
    struct datum * entry_ptr;

    if ( nerrors == 0 ) {

        HDassert( file_ptr );
        HDassert( ( 0 <= idx ) && ( idx < NUM_DATA_ENTRIES ) );
        HDassert( idx < virt_num_data_entries );

        entry_ptr = &(data[idx]);

	HDassert ( ! (entry_ptr->global_pinned) );
	HDassert ( ! (entry_ptr->local_pinned) );
	HDassert ( ! ( dirty && ( ! global ) ) );

	lock_entry(file_ptr, idx);

	if ( dirty ) {

	    flags |= H5AC__DIRTIED_FLAG;
	}

	unlock_entry(file_ptr, idx, flags);

        HDassert( (entry_ptr->header).is_pinned );
	HDassert( ( ! dirty ) || ( (entry_ptr->header).is_dirty ) );

	if ( global ) {

	    entry_ptr->global_pinned = TRUE;

	    global_pins++;

	} else {

	    entry_ptr->local_pinned = TRUE;

	    local_pins++;

	}
    }

    return;

}
