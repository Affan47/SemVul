get_option_val(char* option, char* def)
{
  char* c = (option != NULL) ? option : def;
  return c;
}
