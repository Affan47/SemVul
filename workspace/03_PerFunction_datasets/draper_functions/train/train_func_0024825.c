_cleanup_get_all_subdirs (gftp_transfer * transfer, char *oldfromdir,
                          char *oldtodir,
                          void (*update_func) (gftp_transfer * transfer))
{
  if (update_func != NULL)
    {
      transfer->numfiles = transfer->numdirs = -1;
      update_func (transfer);
    }

  if (oldfromdir != NULL)
    g_free (oldfromdir);

  if (oldtodir != NULL)
    g_free (oldtodir);
}
