reload_redir_template(void)
{
struct stat sb;
int	rc, size;
char	*in_mem;

    rc = stat(redir_template, &sb);
    if ( rc != -1 ) {
	if ( sb.st_mtime <= template_mtime )
	    return;
	if ( !redir_template[0] )
	    return;
	my_xlog(LOG_NOTICE|LOG_DBG|LOG_INFORM, "reload_redir_template(): Loading template from `%s'\n", redir_template);

	size   = sb.st_size;
	WRLOCK_REDIR_CONFIG ;
	if ( template ) xfree(template);
	template = NULL;

	in_mem = malloc(size+1);
	if ( in_mem ) {
	    int fd = open(redir_template, O_RDONLY);
	    if ( fd != -1 ) {
		if ( read(fd, in_mem, size) == size ) {
		    template	= in_mem;
		    template_size	= size;
		    template_mtime	= sb.st_mtime;
		    template[size]	= 0;
    		    template_check_time = global_sec_timer;
		} else {
		    verb_printf("reload_redir_template(): Read failed: %m\n");
		    xfree(in_mem);
		}
		close(fd);
	    }  else {
		verb_printf("reload_redir_template(): Open(%s) failed: %m\n", redir_template);
		xfree(in_mem);
	    }
	}
	UNLOCK_REDIR_CONFIG;
    }
}
