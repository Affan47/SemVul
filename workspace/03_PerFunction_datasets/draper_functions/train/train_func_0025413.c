handle_sigpipe(void)
{
    struct sigaction	sig_act;

    sig_act.sa_handler = sigpipe_handler;
    sigemptyset(&sig_act.sa_mask);
    sig_act.sa_flags = 0;
    if (sigaction(SIGPIPE, &sig_act, NULL) < 0)
	perror("knews: sigaction");
}
