_sigchld_handler(int sig __attribute__((unused)))
{
	while (wait4(-1, NULL, WNOHANG | WUNTRACED, NULL) > 0) ;
}
