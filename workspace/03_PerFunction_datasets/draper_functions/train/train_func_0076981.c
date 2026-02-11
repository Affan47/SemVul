cpr_get_hidden( const char *keyword, const char *prompt )
{
    char *p;

    if( opt.command_fd != -1 )
	return do_get_from_fd ( keyword, 1, 0 );
#ifdef USE_SHM_COPROCESSING
    if( opt.shm_coprocess )
	return do_shm_get( keyword, 1, 0 );
#endif
    for(;;) {
	p = tty_get_hidden( prompt );
	if( *p == '?' && !p[1] ) {
	    xfree(p);
	    display_online_help( keyword );
	}
	else
	    return p;
    }
}
