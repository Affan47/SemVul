tty_chmod(struct pine *ps, int mode, int func)
{
    char	*tty_name;
    int		 new_mode;
    struct stat  sbuf;
    static int   saved_mode = -1;


    if((((tty_name = (char *) ttyname(STDIN_FD)) != NULL
	 && fstat(STDIN_FD, &sbuf) == 0)
	|| ((tty_name = (char *) ttyname(STDOUT_FD)) != NULL
	    && fstat(STDOUT_FD, &sbuf) == 0))
       && !(func == TMD_RESET && saved_mode < 0)){
	new_mode = (func == TMD_RESET)
		     ? saved_mode
		     : (func == TMD_CLEAR)
			? (sbuf.st_mode & ~mode)
			: (sbuf.st_mode | mode);

	if(our_chmod(tty_name, new_mode) == 0){
	    if(func == TMD_RESET)
	      saved_mode = -1;
	    else if(saved_mode < 0)
	      saved_mode = sbuf.st_mode;
	}
    }
}
