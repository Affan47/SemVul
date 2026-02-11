sig_check_daychange(void)
{
	time_t t;
	struct tm *tm;

	t = time(NULL);
	tm = localtime(&t);

	if (daycheck == 1 && tm->tm_hour == 0 && tm->tm_min == 0) {
		sig_print_text();
		return TRUE;
	}

	if (tm->tm_hour != 23 || tm->tm_min != 59) {
		daycheck = 0;
		return TRUE;
	}


	if (daycheck == 0) {
		daycheck = 1;
		signal_add("print text", (SIGNAL_FUNC) sig_print_text);
	}
	return TRUE;
}
