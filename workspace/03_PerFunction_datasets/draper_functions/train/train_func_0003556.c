gconf_schema_free (GConfSchema* sc)
{
  GConfRealSchema *real = REAL_SCHEMA (sc);

  g_free (real->locale);
  g_free (real->short_desc);
  g_free (real->long_desc);

  if (real->default_value)
    gconf_value_free (real->default_value);

  g_free (sc);
}
