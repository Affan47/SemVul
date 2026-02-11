run_single_test(const char *test, test_function tfunc)
{
	PID_TYPE	pid;
	_stringlist *resultfiles = NULL;
	_stringlist *expectfiles = NULL;
	_stringlist *tags = NULL;
	_stringlist *rl,
			   *el,
			   *tl;
	bool		differ = false;

	status(_("test %-20s ... "), test);
	pid = (tfunc) (test, &resultfiles, &expectfiles, &tags);
	wait_for_tests(&pid, NULL, 1);


	for (rl = resultfiles, el = expectfiles, tl = tags;
		 rl != NULL;
		 rl = rl->next, el = el->next)
	{
		bool		newdiff;

		if (tl)
			tl = tl->next;


		newdiff = results_differ(test, rl->str, el->str);
		if (newdiff && tl)
		{
			printf("%s ", tl->str);
		}
		differ |= newdiff;
	}

	if (differ)
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
