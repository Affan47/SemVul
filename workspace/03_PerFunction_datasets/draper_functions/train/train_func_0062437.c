jobadd(pid_t pid)
{
   int i;

   if (pid < 1)
      return 0;

   for (i = 0; i < MAXJOBS; i++)
	{
		if (jobs[i].pid == 0)
		{
         jobs[i].pid = pid;
         return 1;
      }
   }

   return 0;

}
