audit_log_n_untrustedstring(struct audit_buffer *ab, const char *string,
				 size_t len)
{
	if (audit_string_contains_control(string, len))
		audit_log_n_hex(ab, string, len);
	else
		audit_log_n_string(ab, string, len);
}
