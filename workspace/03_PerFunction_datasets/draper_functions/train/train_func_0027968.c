dconf_shm_open (const gchar *name)
{
  const gchar *shmdir;
  gchar *filename;
  void *memory;
  gint fd;

  shmdir = dconf_shm_get_shmdir ();
  filename = g_build_filename (shmdir, name, NULL);
  memory = NULL;
  fd = -1;

  if (g_mkdir_with_parents (shmdir, 0700) != 0)
    {
      g_critical ("unable to create directory '%s': %s.  dconf will not work properly.", shmdir, g_strerror (errno));
      goto out;
    }

  fd = open (filename, O_RDWR | O_CREAT, 0600);
  if (fd == -1)
    {
      g_critical ("unable to create file '%s': %s.  dconf will not work properly.", filename, g_strerror (errno));
      goto out;
    }


  if (pwrite (fd, "", 1, 1) != 1)
    {
      g_critical ("failed to allocate file '%s': %s.  dconf will not work properly.", filename, g_strerror (errno));
      goto out;
    }

  memory = mmap (NULL, 1, PROT_READ, MAP_SHARED, fd, 0);
  g_assert (memory != MAP_FAILED);
  g_assert (memory != NULL);

 out:
  g_free (filename);
  close (fd);

  return memory;
}
