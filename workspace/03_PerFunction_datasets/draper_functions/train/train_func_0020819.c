view_complete_cb (GObject *object,
                  ECalendarStatus status,
                  const gchar *error_msg,
                  GMainLoop *loop)
{
	test_print ("View complete (status: %d, error_msg:%s\n", status, error_msg ? error_msg : "NULL");

	subtest_passed (SUBTEST_VIEW_DONE, loop);
}
