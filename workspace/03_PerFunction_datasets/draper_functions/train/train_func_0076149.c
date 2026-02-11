cheese_effect_load_from_file (const gchar *filename)
{
  const gchar GROUP_NAME[] = "Effect";
  gchar        *name, *desc;
  GError       *err = NULL;
  CheeseEffect *effect = NULL;
  GKeyFile     *keyfile = g_key_file_new ();

  g_key_file_load_from_file (keyfile, filename, G_KEY_FILE_NONE, &err);
  if (err != NULL)
    goto err_keyfile_load;

  name = g_key_file_get_locale_string (keyfile, GROUP_NAME, "Name", NULL, &err);
  if (err != NULL)
    goto err_name;

  desc = g_key_file_get_string (keyfile, GROUP_NAME, "PipelineDescription", &err);
  if (err != NULL)
    goto err_desc;

  g_key_file_free (keyfile);

  effect = cheese_effect_new (name, desc);
  g_free (name);
  g_free (desc);

  return effect;

err_desc:
    g_free (name);
err_name:
err_keyfile_load:
    g_key_file_free (keyfile);
    g_warning ("CheeseEffect: couldn't load file %s: %s", filename, err->message);
    g_clear_error (&err);
    return NULL;
}
