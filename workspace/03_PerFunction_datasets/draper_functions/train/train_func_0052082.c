settings_set_string( char **string_setting, const char *value )
{


  if( *string_setting == value ) return;

  if( *string_setting ) libspectrum_free( *string_setting );
  *string_setting = utils_safe_strdup( value );
}
