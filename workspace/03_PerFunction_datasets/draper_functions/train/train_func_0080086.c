unload_data_unref (unload_data *data)
{
	gint32 count;
	do {
		mono_atomic_load_acquire (count, gint32, &data->refcount);
		g_assert (count >= 1 && count <= 2);
		if (count == 1) {
			g_free (data);
			return;
		}
	} while (InterlockedCompareExchange (&data->refcount, count, count - 1) != count);
}
