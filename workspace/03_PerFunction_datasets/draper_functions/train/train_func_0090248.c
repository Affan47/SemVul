FormatJobs(xstring& s,const QueueJob *job, int v, const char *plur) const
{
   if(v < 1)
      return s;

   const char *pwd = 0, *lpwd = 0;
   if(v == PrintRequeue)
   {
      for(const QueueJob *j = job; j; j=j->next)
      {
	 if(xstrcmp(pwd, job->pwd))
	 {
	    s.append("cd ").append_quoted(job->pwd).append(" &\n");
	    pwd = job->pwd;
	 }

	 if(xstrcmp(lpwd, job->lpwd))
	 {
	    s.append("lcd ").append_quoted(job->lpwd).append(" &\n");
	    lpwd = job->lpwd;
	 }

	 s.append("queue ").append_quoted(job->cmd).append('\n');
      }
      return s;
   }

   int job_count=JobCount(job);
   if(job_count>1)
      s.appendf("%s:\n", plural(plur,job_count));

   pwd = cur_pwd;
   lpwd = cur_lpwd;

   int n = 1;
   for(const QueueJob *j = job; j; j=j->next)
   {


      if(xstrcmp(pwd, job->pwd))
      {
	 if(v > 2) {
	    s.append("\tcd ").append_quoted(job->pwd).append('\n');
	 }
	 pwd = job->pwd;
      }

      if(xstrcmp(lpwd, job->lpwd))
      {
	 if(v > 2) {
	    s.append("\tlcd ").append_quoted(job->lpwd).append('\n');
	 }
	 lpwd = job->lpwd;
      }

      if(job_count==1)
	 s.appendf("%s: ", plural(plur,job_count));
      else
	 s.appendf("\t%2d. ",n++);

      s.append(j->cmd.get()).append('\n');
   }
   return s;
}
