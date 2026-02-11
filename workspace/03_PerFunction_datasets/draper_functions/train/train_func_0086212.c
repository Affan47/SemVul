get_bm_filename (DialogData *data)
{
  gchar *ret = NULL;
  gchar *bench_dir = NULL;
  const gchar *id = NULL;

  id = udisks_block_get_id (data->block);
  if (id == NULL || strlen (id) == 0)
    goto out;

  bench_dir = g_strdup_printf ("%s/gnome-disks/benchmarks", g_get_user_cache_dir ());
  if (g_mkdir_with_parents (bench_dir, 0777) != 0)
    {
      g_warning ("Error creating directory %s: %m", bench_dir);
      goto out;
    }

  ret = g_strdup_printf ("%s/%s.gnome-disks-benchmark", bench_dir, id);

 out:
  g_free (bench_dir);
  return ret;
}
