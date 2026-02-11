mp750_finish_scan (pixma_t * s)
{
  int error;
  mp750_t *mp = (mp750_t *) s->subdriver;

  switch (mp->state)
    {
    case state_transfering:
      drain_bulk_in (s);

    case state_scanning:
    case state_warmup:
      error = abort_session (s);
      if (abort_session (s) == PIXMA_ECANCELED)
	read_error_info (s, NULL, 0);

    case state_finished:
      if (s->param->source == PIXMA_SOURCE_FLATBED)
	{
	    query_status (s);
	  if (abort_session (s) == PIXMA_ECANCELED)
	    {
	      read_error_info (s, NULL, 0);
	      query_status (s);
	    }
	}
      query_status (s);
        activate (s, 0);
      if (mp->needs_abort)
	{
	  mp->needs_abort = 0;
	  abort_session (s);
	}
      free (mp->buf);
      mp->buf = mp->rawimg = NULL;
      mp->state = state_idle;

    case state_idle:
      break;
    }
}
