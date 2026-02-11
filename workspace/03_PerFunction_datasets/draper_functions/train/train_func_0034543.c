_uid(Request& r, MethodParams& params) {
	Value& obj=params.as_no_junction(0, "object must not be code");

	char local_buf[MAX_NUMBER];
	int size=snprintf(local_buf, sizeof(local_buf), "%p", &obj);

	r.write_pass_lang(*new String(pa_strdup(local_buf, (size_t)size), String::L_CLEAN, size));
}
