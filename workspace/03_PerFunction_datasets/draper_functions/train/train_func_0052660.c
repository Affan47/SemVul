run_single_test(const char *test)
{
	PID_TYPE	pid;

	status(_("test %-20s ... "), test);
	pid = psql_start_test(test);
	wait_for_tests(&pid, NULL, 1);

	if (results_differ(test))
	{
		status(_("FAILED"));
		fail_count++;
	}
	else
	{
		status(_("ok"));
		success_count++;
	}
	status_end();
}
