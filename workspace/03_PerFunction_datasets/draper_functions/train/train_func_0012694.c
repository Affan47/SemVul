tend_children()


{
    int j;
    int status;

    j = 0;
    while (j < njobs)
    {
	if (job_array[j]->mailer_pid != 0 &&
	    xwait(job_array[j]->mailer_pid, &status))
	    tend_mailer(job_array[j], status);
	if (job_array[j]->job_pid != 0 &&
	    xwait(job_array[j]->job_pid, &status))
	    tend_job(job_array[j], status);
	j++;
    }
}
