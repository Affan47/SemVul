trace_file_timeout(ErlDrvData handle) {
    TraceFileData *data = (TraceFileData *) handle;
    if (data->wrap) {
	if (wrap_file(data) < 0) {
	    driver_failure_posix(data->port, errno);
	    return;
	} else {
	    driver_set_timer(data->port, data->wrap->time);
	}
    }
}
