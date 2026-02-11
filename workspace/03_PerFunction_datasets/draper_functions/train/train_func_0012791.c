launch_job(job_rec *jr)
{
    pid_t pid;
    int fd;
    char hostname[512];
    char *mailto;


    if (gethostname(hostname, 512)) {
      strcpy (hostname,"unknown machine");
    }

    setup_env(jr);


    mailto = getenv("MAILTO");

    if (mailto)
	    jr->mailto = mailto;
    else
	    jr->mailto = username ();


    fd = jr->output_fd = temp_file();

    xwrite(fd, "From: ");
    xwrite(fd, "Anacron <");
    xwrite(fd, username());
    xwrite(fd, ">\n");
    xwrite(fd, "To: ");
    if (mailto) {
       xwrite(fd, mailto);
    } else {
       xwrite(fd, username());
    }
    xwrite(fd, "\n");
    xwrite(fd, "Subject: Anacron job '");
    xwrite(fd, jr->ident);
    xwrite(fd, "' on ");
    xwrite(fd, hostname);
    xwrite(fd, "\n");
    xwrite(fd, "Content-Type: text/plain; charset=");
    xwrite(fd, mail_charset);
    xwrite(fd, "\n\n");

    jr->mail_header_size = file_size(fd);

    pid = xfork();
    if (pid == 0)
    {

	in_background = 1;
	run_job(jr);

    }

    explain("Job `%s' started", jr->ident);
    jr->job_pid = pid;
    running_jobs++;
}
