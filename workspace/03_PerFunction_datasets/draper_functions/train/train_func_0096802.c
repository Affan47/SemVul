gdata_tear_down_async_test_data (GDataAsyncTestData *async_data, gconstpointer test_data)
{
	g_assert (async_data->test_data == test_data);

	g_object_unref (async_data->cancellable);
	g_main_loop_unref (async_data->main_loop);
}
