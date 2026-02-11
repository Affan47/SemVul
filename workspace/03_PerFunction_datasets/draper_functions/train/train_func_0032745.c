cr_string_new_from_string (const gchar * a_string)
{
	CRString *result = cr_string_new () ;
	if (!result) {
		cr_utils_trace_info ("Out of memory") ;
		return NULL ;
	}
	if (a_string)
		g_string_append (result->stryng, a_string) ;
	return result ;
}
