main(int argc, char *argv[])
{
	const char *dbpath;
	setup_signals();
	bandb_helper = rb_helper_child(parse_request, error_cb, NULL, NULL, NULL, 256, 256, 256, 256);
	if(bandb_helper == NULL)
	{
		fprintf(stderr,
			"This is ircd-ratbox bandb.  You aren't supposed to run me directly. Maybe you want bantool?\n");
		fprintf(stderr,
			"However I will print my Id tag $Id: bandb.c 27371 2012-03-16 05:33:15Z dubkat $\n");
		fprintf(stderr, "Have a nice day\n");
		exit(1);
	}
	dbpath = getenv("BANDB_DPATH");
	if(dbpath == NULL)
		dbpath = DBPATH;

	rsdb_init(dbpath, db_error_cb);
	check_schema();
	rb_helper_loop(bandb_helper, 0);

	return 0;
}
