wi_mutable_string_append_format(wi_mutable_string_t *string, wi_string_t *fmt, ...) {
	va_list			ap;

	WI_RUNTIME_ASSERT_MUTABLE(string);

	va_start(ap, fmt);
	_wi_string_append_arguments(string, wi_string_cstring(fmt), ap);
	va_end(ap);
}
