posix_openlog(s48_call_t call,
	      s48_ref_t sch_ident, s48_ref_t sch_options, s48_ref_t sch_facility)
{
  if (syslog_open)
    s48_assertion_violation_2(call,
			      "posix_openlog", "syslog is already open",
			      3, sch_ident, sch_options, sch_facility);

  {


    char* ident = s48_extract_byte_vector_readonly_2(call, sch_ident);
    size_t ident_size = strlen(ident) + 1;
    if (ident_size > syslog_ident_size)
      {
	if (syslog_ident != syslog_ident_initial)
	  free(syslog_ident);
	syslog_ident = malloc(ident_size);
	if (syslog_ident == NULL)
	  s48_out_of_memory_error_2(call);
	syslog_ident_size = ident_size;
      }
    strcpy(syslog_ident, ident);

  openlog(syslog_ident,
	  extract_syslog_options(call, sch_options),
	  extract_syslog_facility(call, sch_facility));
  }
  syslog_open = 1;
  return s48_unspecific_2(call);
}
