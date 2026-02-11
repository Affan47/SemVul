lock_and_unlock_random_entry(H5F_t * file_ptr,
                             int min_idx,
                             int max_idx)
{

    int idx;

    if ( nerrors == 0 ) {

        HDassert( file_ptr );
        HDassert( 0 <= min_idx );
        HDassert( min_idx < max_idx );
        HDassert( max_idx < NUM_DATA_ENTRIES );
        HDassert( max_idx < virt_num_data_entries );

        idx = (HDrand() % (max_idx - min_idx)) + min_idx;

        HDassert( min_idx <= idx );
        HDassert( idx <= max_idx );

	lock_entry(file_ptr, idx);
	unlock_entry(file_ptr, idx, H5AC__NO_FLAGS_SET);
    }

    return;

}
