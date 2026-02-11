print_schema_in_xml(GConfValue* value, int indent)
{
  GConfSchema* schema;
  GConfValueType type;
  GConfValueType list_type;
  GConfValueType car_type;
  GConfValueType cdr_type;
  GConfValue* default_value;
  const gchar* owner;
  const gchar* short_desc;
  const gchar* long_desc;
  gchar* whitespace;

  whitespace = g_strnfill(indent, ' ');

  schema = gconf_value_get_schema(value);

  type = gconf_schema_get_type(schema);
  list_type = gconf_schema_get_list_type(schema);
  car_type = gconf_schema_get_car_type(schema);
  cdr_type = gconf_schema_get_cdr_type(schema);

  owner = gconf_schema_get_owner(schema);
  default_value = gconf_schema_get_default_value(schema);
  short_desc = gconf_schema_get_short_desc(schema);
  long_desc = gconf_schema_get_long_desc(schema);

  g_print ("%s<schema>\n", whitespace);

  if (owner)
    g_print ("%s  <owner>%s</owner>\n", whitespace, owner);

  g_print ("%s  <type>%s</type>\n", whitespace, gconf_value_type_to_string(type));

  if (type == GCONF_VALUE_LIST)
    g_print ("%s  <list_type>%s</list_type>\n", whitespace, gconf_value_type_to_string(list_type));
  else if (type == GCONF_VALUE_PAIR)
    {
      g_print ("%s  <car_type>%s</car_type>\n", whitespace, gconf_value_type_to_string(car_type));
      g_print ("%s  <cdr_type>%s</cdr_type>\n", whitespace, gconf_value_type_to_string(cdr_type));
    }

  g_print ("%s  <locale name=\"%s\">\n", whitespace, gconf_schema_get_locale (schema));

  if (default_value)
    {
      g_print ("%s    <default_value>\n", whitespace);
      print_value_in_xml(default_value, indent + 6);
      g_print ("%s    </default_value>\n", whitespace);
    }

  if (short_desc)
    {
      gchar* tmp = g_markup_escape_text(short_desc, -1);
      g_print ("%s    <short>%s</short>\n", whitespace, tmp);
      g_free(tmp);
    }

  if (long_desc)
    {
      gchar* tmp = g_markup_escape_text(long_desc, -1);
      g_print ("%s    <long>%s</long>\n", whitespace, tmp);
      g_free(tmp);
    }

  g_print ("%s  </locale>\n", whitespace);

  g_print ("%s</schema>\n", whitespace);

  g_free(whitespace);
}
