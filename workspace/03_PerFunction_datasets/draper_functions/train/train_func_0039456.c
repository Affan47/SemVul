substitute_null_characters( char *string, int len ) {
  char histogram[ 256 ];


  histogramCharacters( string, len, histogram, 1 );


  if ( histogram[ ( unsigned char ) mNullSubsChar ] != 0 ) {
    char * bufString;
    char newSubsChar;
    bufString = (char*)text();
    histogramCharacters( bufString, mLength, histogram, 0 );
    newSubsChar = chooseNullSubsChar( histogram );
    if ( newSubsChar == '\0' )
      return 0;
    subsChars( bufString, mLength, mNullSubsChar, newSubsChar );
    remove_( 0, mLength );
    insert_( 0, bufString );
    free( (void *) bufString );
    mNullSubsChar = newSubsChar;
  }


  if ( histogram[ 0 ] != 0 )
    subsChars( string, len, '\0', mNullSubsChar );
  return 1;
}
