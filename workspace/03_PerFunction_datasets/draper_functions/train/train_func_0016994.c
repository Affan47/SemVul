test_misc ()
{
	const char *home = g_get_home_dir ();
	const char *tmp = g_get_tmp_dir ();

	if (home == NULL)
		return FAILED ("Where did my home go?");

	if (tmp == NULL)
		return FAILED ("Where did my /tmp go?");

	return OK;
}
