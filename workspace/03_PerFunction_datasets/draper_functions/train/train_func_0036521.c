posix_compile_regexp(s48_call_t call, s48_ref_t pattern,
		     s48_ref_t extended_p, s48_ref_t ignore_case_p,
		     s48_ref_t submatches_p, s48_ref_t newline_p)
{
  s48_ref_t sch_regex;
  int status;
  int flags =
    (s48_extract_boolean_2(call, extended_p)    ? REG_EXTENDED : 0) |
    (s48_extract_boolean_2(call, ignore_case_p) ? REG_ICASE    : 0) |
    (s48_extract_boolean_2(call, submatches_p)  ? 0 : REG_NOSUB) |
    (s48_extract_boolean_2(call, newline_p)     ? REG_NEWLINE  : 0);

  s48_check_byte_vector_2(call, pattern);

  sch_regex = s48_make_value_2(call, regex_t);

  status = regcomp(s48_unsafe_extract_value_pointer_2(call, sch_regex, regex_t),
		   s48_extract_byte_vector_readonly_2(call, pattern),
		   flags);

  if (status == 0)
    return sch_regex;
  else
    return s48_enter_long_2(call, status);
}
