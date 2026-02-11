dead_file_copy_init(void)
{
	gfarm_error_t e;

	e = db_deadfilecopy_load(NULL, dead_file_copy_add_one);
	if (e != GFARM_ERR_NO_ERROR && e != GFARM_ERR_NO_SUCH_OBJECT)
		gflog_error(GFARM_MSG_1000362,
		    "loading deadfilecopy: %s", gfarm_error_string(e));

	host_busyq_scanner_init();

	e = create_detached_thread(removal_finalizer, NULL);
	if (e != GFARM_ERR_NO_ERROR)
		gflog_fatal(GFARM_MSG_1002235,
		    "create_detached_thread(removal_finalizer): %s",
		    gfarm_error_string(e));

}
