uip_cleanse_string (const sc_char *original, sc_char *buffer, sc_int length)
{
  sc_int required;
  sc_char *string;


  required = strlen (original) + 1;
  string = (required < length) ? buffer : sc_malloc (required);
  strcpy (string, original);


  sc_trim_string (string);
  return string;
}
