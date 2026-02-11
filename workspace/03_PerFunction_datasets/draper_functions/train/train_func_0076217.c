journal_seek(dns_journal_t *j, isc_uint32_t offset) {
	isc_result_t result;

	result = isc_stdio_seek(j->fp, (off_t)offset, SEEK_SET);
	if (result != ISC_R_SUCCESS) {
		isc_log_write(JOURNAL_COMMON_LOGARGS, ISC_LOG_ERROR,
			      "%s: seek: %s", j->filename,
			      isc_result_totext(result));
		return (ISC_R_UNEXPECTED);
	}
	j->offset = offset;
	return (ISC_R_SUCCESS);
}
