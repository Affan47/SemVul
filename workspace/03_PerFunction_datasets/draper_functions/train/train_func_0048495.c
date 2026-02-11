gftpui_common_cancel_file_transfer (gftp_transfer * tdata)
{
  g_static_mutex_lock (&tdata->structmutex);

  if (tdata->started)
    {
      gftpui_cancel_file_transfer (tdata);
      tdata->skip_file = 0;
    }
  else
    tdata->done = 1;

  tdata->fromreq->stopable = 0;
  tdata->toreq->stopable = 0;

  g_static_mutex_unlock (&tdata->structmutex);

  tdata->fromreq->logging_function (gftp_logging_misc, tdata->fromreq,
                                    _("Stopping the transfer on host %s\n"),
                                    tdata->toreq->hostname);
}
