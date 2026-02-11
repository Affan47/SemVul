LoadUnitTypes( MemBuffer &file ) {
  ut = new UnitType [num_tiles];
  if ( !ut ) return -1;

  int rc = 0;

  for ( int i = 0; i < num_tiles; ++i ) {
    if ( ut[i].Load( file, this ) ) {
      rc = -1;
      break;
    }
  }


  if ( rc == 0 )
    rc = unit_names.Load( file );

  if ( rc == -1 ) {
      delete [] ut;
      ut = NULL;
      num_tiles = 0;
      return -1;
  }

  SetLocale( CF_LANG_DEFAULT );
  return 0;
}
