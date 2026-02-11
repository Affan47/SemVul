aut_warning( Warning, Text, File, Line )

  int   Warning;
  char *Text;
  char *File;
  long  Line;
{
  char *Name;

  Name = mbkstrdup( File );
  Name[ strlen( File ) - 1 ] = '\0';

  fprintf( stderr, "%s%ld ", Name, Line );

  switch( Warning )
  {
    case AUT_EXIT_CORE_WARNING :
      fprintf( stderr, "warning: abnormal autexit generates a core file !\n" );
    break;

    case AUT_ALLOC_DEBUG_WARNING :
      fprintf( stderr, "warning: autalloc and autfree debug mode on !\n" );
    break;

    case AUT_ABNORMAL_EXIT_WARNING :
      fprintf( stderr, "warning: abnormal autexit %ld !\n", (long)Text );
    break;

    default :

      fprintf( stderr, "unknown internal warning %d !\n", Warning );
  }
}
