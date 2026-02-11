trace_begin (const char *filename,
			  const char *file, int line)
{
	tracefile_header_t tfh;
	int status;
	trace_type_t *tptr, *next;
	isc_result_t result;

	if (traceoutfile) {
		log_error ("%s(%d): trace_begin called twice",
			   file, line);
		return DHCP_R_INVALIDARG;
	}

	traceoutfile = open (filename, O_CREAT | O_WRONLY | O_EXCL, 0600);
	if (traceoutfile < 0 && errno == EEXIST) {
		log_error ("WARNING: Overwriting trace file \"%s\"", filename);
		traceoutfile = open (filename, O_WRONLY | O_EXCL | O_TRUNC,
				     0600);
	}

	if (traceoutfile < 0) {
		log_error ("%s(%d): trace_begin: %s: %m",
			   file, line, filename);
		return ISC_R_UNEXPECTED;
	}
#if defined (HAVE_SETFD)
	if (fcntl (traceoutfile, F_SETFD, 1) < 0)
		log_error ("Can't set close-on-exec on %s: %m", filename);
#endif

	tfh.magic = htonl (TRACEFILE_MAGIC);
	tfh.version = htonl (TRACEFILE_VERSION);
	tfh.hlen = htonl (sizeof (tracefile_header_t));
	tfh.phlen = htonl (sizeof (tracepacket_t));

	status = write (traceoutfile, &tfh, sizeof tfh);
	if (status < 0) {
		log_error ("%s(%d): trace_begin write failed: %m", file, line);
		return ISC_R_UNEXPECTED;
	} else if (status != sizeof tfh) {
		log_error ("%s(%d): trace_begin: short write (%d:%ld)",
			   file, line, status, (long)(sizeof tfh));
		trace_stop ();
		return ISC_R_UNEXPECTED;
	}


	if (new_trace_types) {
		next = new_trace_types;
		new_trace_types = (trace_type_t *)0;
		for (tptr = next; tptr; tptr = next) {
			next = tptr -> next;
			if (tptr -> index != 0) {
				result = (trace_type_record
					  (tptr,
					   strlen (tptr -> name), file, line));
				if (result != ISC_R_SUCCESS)
					return status;
			}
		}
	}

	return ISC_R_SUCCESS;
}
