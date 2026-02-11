log_is_managed(enum log_file which)
{
	log_file_check(which);

	return logfile[which].path != NULL && !logfile[which].changed;
}
