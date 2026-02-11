gap_base_get_gimprc_int_value (const char *gimprc_option_name
   , gint32 default_value, gint32 min_value, gint32 max_value)
{
  char *value_string;
  gint32 value;

  value = default_value;

  value_string = gimp_gimprc_query(gimprc_option_name);
  if(value_string)
  {
     value = atol(value_string);
     g_free(value_string);
  }
  return (CLAMP(value, min_value, max_value));

}
