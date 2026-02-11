SaveMission( const char *file, bool filereq ) {
  string fn;
  GUI_Status rc = GUI_OK;

  if ( filereq )
    fn = GetFileName( file, ".lev", mapdir, WIN_FILE_SAVE );
  else fn = file;

  if ( fn.length() > 0 ) {
    if ( mission->Save( fn.c_str() ) != 0 ) {
      new NoteWindow( "Error", "Could not save mission!", WIN_CENTER, view );
    }
  }
  return rc;
}
