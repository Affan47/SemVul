mysystem(const char *command, ErrorHandler *errh)
{
    if (no_create) {
	errh->message("would run %s", command);
	return 0;
    } else {
	if (verbose)
	    errh->message("running %s", command);
	return system(command);
    }
}
