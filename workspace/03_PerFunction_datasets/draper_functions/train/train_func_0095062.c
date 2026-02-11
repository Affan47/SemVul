read_stdin_char(char *c)
{
    int rv;


    while(1){
	rv = read(PIPED_FD, c, 1);
	if(rv < 0){
	    if(errno == EINTR){
		dprint((2, "read_stdin_char: read interrupted, restarting\n"));
		continue;
	    }
	    else
	      dprint((1, "read_stdin_char: read FAILED: %s\n",
			 error_description(errno)));
	}
	break;
    }
    return(rv);
}
