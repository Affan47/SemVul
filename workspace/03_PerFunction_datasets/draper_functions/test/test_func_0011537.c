__aio_remove_request (struct requestlist *last, struct requestlist *req,
		      int all)
{
  assert (req->running == yes || req->running == queued
	  || req->running == done);

  if (last != NULL)
    last->next_prio = all ? NULL : req->next_prio;
  else
    {
      if (all || req->next_prio == NULL)
	{
	  if (req->last_fd != NULL)
	    req->last_fd->next_fd = req->next_fd;
	  else
	    requests = req->next_fd;
	  if (req->next_fd != NULL)
	    req->next_fd->last_fd = req->last_fd;
	}
      else
	{
	  if (req->last_fd != NULL)
	    req->last_fd->next_fd = req->next_prio;
	  else
	    requests = req->next_prio;

	  if (req->next_fd != NULL)
	    req->next_fd->last_fd = req->next_prio;

	  req->next_prio->last_fd = req->last_fd;
	  req->next_prio->next_fd = req->next_fd;


	  req->next_prio->running = yes;
	}

      if (req->running == yes)
	{
	  struct requestlist *runp = runlist;

	  last = NULL;
	  while (runp != NULL)
	    {
	      if (runp == req)
		{
		  if (last == NULL)
		    runlist = runp->next_run;
		  else
		    last->next_run = runp->next_run;
		  break;
		}
	      last = runp;
	      runp = runp->next_run;
	    }
	}
    }
}
