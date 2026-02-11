terminate_stopped_jobs ()
{
  register int i;


  for (i = 0; i < js.j_jobslots; i++)
    {
      if (jobs[i] && STOPPED (i))
	{
	  killpg (jobs[i]->pgrp, SIGTERM);
	  killpg (jobs[i]->pgrp, SIGCONT);
	}
    }
}
