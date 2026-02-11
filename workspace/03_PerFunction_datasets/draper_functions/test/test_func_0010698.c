autosave_prune( void )
{
  GArray *autosaves = g_array_new( FALSE, FALSE, sizeof( prune_info_t ) );
  libspectrum_rzx_iterator it;
  size_t i, frames = 0;

  for( it = libspectrum_rzx_iterator_begin( rzx );
       it;
       it = libspectrum_rzx_iterator_next( it ) ) {

    libspectrum_rzx_block_id id = libspectrum_rzx_iterator_get_type( it );

    switch( id ) {

    case LIBSPECTRUM_RZX_INPUT_BLOCK:
      frames += libspectrum_rzx_iterator_get_frames( it ); break;

    case LIBSPECTRUM_RZX_SNAPSHOT_BLOCK:
      if( libspectrum_rzx_iterator_snap_is_automatic( it ) ) {
        prune_info_t info = { it, frames };
	g_array_append_val( autosaves, info );
      }
      break;

    default:
      break;
    }
  }


  for( i = 0; i < autosaves->len; i++ ) {
    prune_info_t *info = &( g_array_index( autosaves, prune_info_t, i ) );
    info->frames = frames - info->frames;
  }

  for( i = autosaves->len - 1; i > 0; i-- ) {
    prune_info_t save1 = g_array_index( autosaves, prune_info_t, i ),
      save2 = g_array_index( autosaves, prune_info_t, i - 1 );

    if( ( save1.frames == 15 * 50 ||
          save1.frames == 60 * 50 ||
	  save1.frames == 300 * 50   ) &&
	save2.frames < 2 * save1.frames
      )

      libspectrum_rzx_iterator_delete( rzx, save1.it );
  }

  g_array_free( autosaves, TRUE );
}
