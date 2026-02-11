_gftpui_common_cmd_transfer_files (void *fromuidata, gftp_request * fromrequest,
                                   void *touidata, gftp_request * torequest,
                                   const char *cmd, const char *filespec)
{
  gftp_transfer * tdata;
  gftp_file * fle;

  if (!GFTP_IS_CONNECTED (fromrequest) ||
      !GFTP_IS_CONNECTED (torequest))
    {
      fromrequest->logging_function (gftp_logging_error, fromrequest,
                                  _("Error: Not connected to a remote site\n"));
      return;
    }

  if (*filespec == '\0')
    {
      fromrequest->logging_function (gftp_logging_error, fromrequest,
                                     _("usage: %s <filespec>\n"), cmd);
      return;
    }

  tdata = gftp_tdata_new ();
  tdata->fromreq = fromrequest;
  tdata->toreq = torequest;

  if (gftp_list_files (tdata->fromreq) != 0)
    {
      tdata->fromreq = tdata->toreq = NULL;
      free_tdata (tdata);
      return;
    }

  fle = g_malloc0 (sizeof (*fle));
  while (gftp_get_next_file (tdata->fromreq, filespec, fle) > 0)
    {
      if (strcmp (fle->file, ".") == 0 || strcmp (fle->file, "..") == 0)
        {
          gftp_file_destroy (fle, 0);
          continue;
        }

      tdata->files = g_list_append (tdata->files, fle);
      fle = g_malloc0 (sizeof (*fle));
    }

  g_free (fle);

  gftp_end_transfer (tdata->fromreq);

  if (tdata->files == NULL)
    {
      tdata->fromreq = tdata->toreq = NULL;
      free_tdata (tdata);
      return;
    }

  if (gftp_get_all_subdirs (tdata, NULL) != 0)
    {
      tdata->fromreq = tdata->toreq = NULL;
      free_tdata (tdata);
      return;
    }

  if (tdata->files == NULL)
    {
      tdata->fromreq = tdata->toreq = NULL;
      free_tdata (tdata);
      return;
    }

  gftpui_common_add_file_transfer (tdata->fromreq, tdata->toreq,
                                   fromuidata, touidata, tdata->files);

  g_free (tdata);

  return;
}
