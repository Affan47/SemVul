thumbnailer_try_exec (Thumbnailer *thumb)
{
  gchar *path;
  gboolean retval;

  if (G_UNLIKELY (!thumb))
    return FALSE;


  if (!thumb->try_exec)
    return TRUE;

  path = g_find_program_in_path (thumb->try_exec);
  retval = path != NULL;
  g_free (path);

  return retval;
}
