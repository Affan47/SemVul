abl_error( Error, Text, File, Line )

  int   Error;
  char *Text;
  char *File;
  long  Line;
{
  char *Name;

  Name = mbkstrdup( File );
  Name[ strlen( File ) - 1 ] = '\0';

  fprintf( stderr, "%s%ld ", Name, Line );

  switch( Error )
  {
    case ABL_OPERATOR_ERROR :

      fprintf( stderr, "bad operator %ld !\n", (long)Text );

    break;

    case ABL_NOT_UNARY_ERROR :

      fprintf( stderr, "not unary operator %ld !\n", (long)Text );

    break;

    default :

      fprintf( stderr, "unknown internal error %d !\n", Error );
  }

  autexit( 1 );
}
