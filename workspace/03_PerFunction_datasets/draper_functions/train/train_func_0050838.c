autosave_frame( void )
{
  libspectrum_snap *snap;

  if( ++autosave_frame_count % AUTOSAVE_INTERVAL ) return;

  snap = libspectrum_snap_alloc();
  snapshot_copy_to( snap );

  libspectrum_rzx_stop_input( rzx );
  libspectrum_rzx_add_snap( rzx, snap, 1 );
  libspectrum_rzx_start_input( rzx, tstates );

  autosave_prune();
}
