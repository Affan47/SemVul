is_filetype( const char* new_filename, const char* type )
{
  return ( strlen( new_filename ) >= strlen(type) &&
           !strcasecmp( new_filename + (strlen( new_filename ) - strlen(type) ),
                        type ) );
}
