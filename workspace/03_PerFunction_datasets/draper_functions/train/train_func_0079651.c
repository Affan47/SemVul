benchmark_run (gint argc, gchar *argv [])
{
  gchar *base_dir;
  gchar *scratch_file;
  gint   i;

  setlocale (LC_ALL, "");

  if (argc < 2)
    {
      g_printerr ("Usage: %s <scratch path>\n", argv [0]);
      return 1;
    }

  base_dir = argv [1];

  if (!is_dir (base_dir))
    {
      g_printerr ("Scratch path %s is not a directory\n", argv [1]);
      return 1;
    }

  for (i = 0; i < ITERATIONS_NUM; i++)
    {
      scratch_file = create_file (base_dir);
      if (!scratch_file)
        {
          g_free (base_dir);
          return 1;
        }

      read_file (scratch_file);
      delete_file (scratch_file);

      g_free (scratch_file);
    }

  return 0;
}
