finish_thread_test (ThreadData *data)
{
	g_assert_cmpint (data->n_contacts, ==, N_CONTACTS);

	g_main_loop_quit (data->loop);
	g_thread_join (data->thread);
	g_mutex_clear (&data->complete_mutex);
	g_cond_clear (&data->complete_cond);
	g_slice_free (ThreadData, data);
}
