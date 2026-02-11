lutil_sigaction(int sig, lutil_sig_t func)
{
	struct sigaction action, oaction;

	memset( &action, '\0', sizeof(action) );

	action.sa_handler = func;
	sigemptyset( &action.sa_mask );
#ifdef SA_RESTART
	action.sa_flags |= SA_RESTART;
#endif

	if( sigaction( sig, &action, &oaction ) != 0 ) {
		return NULL;
	}

	return oaction.sa_handler;
}
