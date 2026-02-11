rzx_rollback_to( void )
{
  GSList *rollback_points;
  libspectrum_snap *snap;
  int which, error;

  rollback_points = get_rollback_list( rzx );

  which = ui_get_rollback_point( rollback_points );

  if( which == -1 ) return 1;

  error = libspectrum_rzx_rollback_to( rzx, &snap, which );
  if( error ) return error;

  error = start_after_rollback( snap );
  if( error ) return error;

  return 0;
}
