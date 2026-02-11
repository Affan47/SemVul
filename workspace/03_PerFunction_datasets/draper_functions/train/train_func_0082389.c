ckcmd ( TFILE *f, int *err, char *s, int t, int r )
{
  int c=0 ;
  char *message ;

  if ( ( ! err || ! *err ) && ( c = cmd ( f, s, t ) ) != r && r ) {
    if ( c == EOF ) {
      if ( s ) {
	message = strdup2 ( err ? "E " : "W ", gettext ( "timed out after command: %s" ) ) ;
	if ( message ) {
	  msg ( message, s ) ;
	  free ( message ) ;
	}
      } else {
	msg ( err ? "E %s" : "W %s", gettext ( "timed out after waiting" ) ) ;
      }
    } else {
      if ( s ) {
	message = strdup2 ( err ? "E " : "W ", gettext ( "wrong response after command: %s" ) ) ;
	if ( message ) {
	  msg ( message, s ) ;
	  free ( message ) ;
	}
      } else {
	msg ( err ? "E %s" : "W %s", gettext ( "wrong response after waiting" ) ) ;
      }
    }

    if ( err ) *err = 3 ;
  }
  return c ;
}
