assert_true(TestReporter *reporter, const char *file, int line, int result, const char *message, ...) {
    va_list arguments;
    va_start(arguments, message);
	if (result) {
    	(*reporter->show_pass)(reporter, file, line, message, arguments);
	} else {
    	(*reporter->show_fail)(reporter, file, line, message, arguments);
	}
	add_reporter_result(reporter, result);
	va_end(arguments);
}
