aisleriot_conf_set_options (const char *game_module,
                            int value)
{
#ifdef HAVE_GNOME
  GConfSchema *schema;
  char *gconf_key, *schemas_key;

  gconf_key = options_gconf_key (game_module);

  schemas_key = g_strconcat ("/schemas", gconf_key, NULL);


  schema = gconf_client_get_schema (gconf_client, schemas_key, NULL);
  if (!schema) {
    GConfValue *def;

    schema = gconf_schema_new ();
    gconf_schema_set_type (schema, GCONF_VALUE_INT);
    gconf_schema_set_owner (schema, "aisleriot");

    gconf_schema_set_short_desc (schema, "A per-game option");
    gconf_schema_set_long_desc (schema,
                                "An integer encoding a list of boolean values (LSB = first item) for use as options in a solitaire game.");

    def = gconf_value_new (GCONF_VALUE_INT);


    gconf_value_set_int (def, value);
    gconf_schema_set_default_value_nocopy (schema, def);

    gconf_client_set_schema (gconf_client, schemas_key, schema, NULL);
    gconf_engine_associate_schema (gconf_engine_get_default (), gconf_key, schemas_key, NULL);
  }
  gconf_schema_free (schema);
  g_free (schemas_key);

  gconf_client_set_int (gconf_client, gconf_key, value, NULL);
  g_free (gconf_key);
#else
  char *game_name;

  game_name = game_module_to_game_name (game_module);
  ar_conf_set_integer (game_name, "Options", value);
  g_free (game_name);
#endif
}
