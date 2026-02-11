teardown (Test *test, gconstpointer unused)
{
	if (test->result)
		g_object_unref (test->result);
	if (test->process)
		g_object_unref (test->process);

	while (g_main_context_iteration (NULL, FALSE));

	if (test->result)
		g_assert (test->result == NULL);
	if (test->process)
		g_assert (test->process == NULL);

	if (test->output_buf)
		g_string_free (test->output_buf, TRUE);
	if (test->error_buf)
		g_string_free (test->error_buf, TRUE);
	if (test->attribute_buf)
		g_string_free (test->attribute_buf, TRUE);
	_gcr_record_free (test->record);
}
