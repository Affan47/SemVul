gftpui_common_skip_file_transfer (gftp_transfer * tdata, gftp_file * curfle)
{
  g_static_mutex_lock (&tdata->structmutex);

  if (tdata->started && !(curfle->transfer_action & GFTP_TRANS_ACTION_SKIP))
    {
      curfle->transfer_action = GFTP_TRANS_ACTION_SKIP;
      if (tdata->curfle != NULL && curfle == tdata->curfle->data)
        {
          gftpui_cancel_file_transfer (tdata);
          tdata->skip_file = 1;
        }
      else if (!curfle->transfer_done)
        tdata->total_bytes -= curfle->size;
    }

  g_static_mutex_unlock (&tdata->structmutex);

  if (curfle != NULL)
    tdata->fromreq->logging_function (gftp_logging_misc, tdata->fromreq,
                                      _("Skipping file %s on host %s\n"),
                                      curfle->file, tdata->toreq->hostname);
}
