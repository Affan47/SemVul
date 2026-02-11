ay_to_strv (GVariant *variant,
            int *argc)
{
  GPtrArray *argv;
  const char *data, *nullbyte;
  gsize data_len;
  gssize len;

  data = g_variant_get_fixed_array (variant, &data_len, sizeof (char));
  if (data_len == 0 || data_len > G_MAXSSIZE) {
    if (argc)
      *argc = 0;

    return NULL;
  }

  argv = g_ptr_array_new ();

  len = data_len;
  do {
    gssize string_len;

    nullbyte = memchr (data, '\0', len);

    string_len = nullbyte ? (gssize) (nullbyte - data) : len;
    g_ptr_array_add (argv, g_strndup (data, string_len));

    len -= string_len + 1;
    data += string_len + 1;
  } while (len > 0);

  if (argc)
    *argc = argv->len;


  g_ptr_array_add (argv, NULL);
  return (char **) g_ptr_array_free (argv, FALSE);
}
