GNUNET_DISK_directory_iterator_start (enum GNUNET_SCHEDULER_Priority prio,
                                      const char *dirName,
                                      GNUNET_DISK_DirectoryIteratorCallback
                                      callback, void *callback_cls)
{
  struct GNUNET_DISK_DirectoryIterator *di;

  di = GNUNET_malloc (sizeof (struct GNUNET_DISK_DirectoryIterator));
  di->callback = callback;
  di->callback_cls = callback_cls;
  di->directory = OPENDIR (dirName);
  if (di->directory == NULL)
  {
    GNUNET_free (di);
    callback (callback_cls, NULL, NULL, NULL);
    return GNUNET_SYSERR;
  }
  di->dirname = GNUNET_strdup (dirName);
  di->priority = prio;
  return GNUNET_DISK_directory_iterator_next (di, GNUNET_NO);
}
