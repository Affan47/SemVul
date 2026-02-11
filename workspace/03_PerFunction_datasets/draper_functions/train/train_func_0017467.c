log_buffer_force_file (struct log_buffer *lb)
{
    lb->log = cvs_temp_file (&lb->back_fn);
    if (!lb->log)
	error (lb->fatal_errors, errno, "failed to open log file.");
}
