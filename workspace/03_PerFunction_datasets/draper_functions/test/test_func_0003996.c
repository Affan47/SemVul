binary_generator (gint argc,
                  struct _ESExpResult **argv,
                  struct _ESExpResult *r)
{
	g_return_val_if_fail (r != NULL, FALSE);
	g_return_val_if_fail (argc == 2, FALSE);

	if ((argv[0]->type != ESEXP_RES_TIME) || (argv[1]->type != ESEXP_RES_TIME))
		return FALSE;

	r->occuring_start = argv[0]->value.time;
	r->occuring_end = argv[1]->value.time;

	return TRUE;
}
