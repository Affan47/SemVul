catch_signal(int sig)
{
    signal(sig, SIG_DFL);
    if (!started)
	kill(getpid(), sig);
    else
	router->set_runcount(Router::STOP_RUNCOUNT);
}
