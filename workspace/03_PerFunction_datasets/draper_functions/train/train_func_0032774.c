lynx_warning( Warning, Text, File, Line )

  char  Warning;
  char *Text;
  char *File;
  long  Line;
{
  char *Name;

  Name = mbkstrdup( File );
  Name[ strlen( File ) - 1 ] = '\0';

  fprintf( stderr, "\n\t%s%ld Warning : ", Name, Line );

  switch( Warning )
  {
    case LYNX_WARNING_PHYSICAL_CONNECTOR    :
      fprintf( stderr, "connector %s is on two different equis !\n", Text );
    break;
    case LYNX_WARNING_CORE_FILE :
      fprintf( stderr, "Generates %s file !\n", Text );
    break;
    default :
      fprintf( stderr, "unknown internal warning %d !\n", Warning );
  }
}
