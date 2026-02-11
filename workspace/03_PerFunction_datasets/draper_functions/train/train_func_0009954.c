insert( int pos, const char *s ) {
  int nInserted;


  if ( pos > mLength ) pos = mLength;
  if ( pos < 0 ) pos = 0;


  call_predelete_callbacks( pos, 0 );


  nInserted = insert_( pos, s );
  mCursorPosHint = pos + nInserted;
  call_modify_callbacks( pos, 0, nInserted, 0, NULL );
}
