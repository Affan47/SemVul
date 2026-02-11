async_send_request_finished (SoupMessage *msg, gpointer user_data)
{
	SoupMessageQueueItem *item = user_data;
	GMemoryOutputStream *mostream;
	GInputStream *istream = NULL;
	GError *error = NULL;

	if (!item->task) {

		return;
	}

	mostream = g_object_get_data (G_OBJECT (item->task), "SoupSession:ostream");
	if (mostream) {
		gpointer data;
		gssize size;


		size = g_memory_output_stream_get_data_size (mostream);
		data = size ? g_memory_output_stream_steal_data (mostream) : g_strdup ("");
		istream = g_memory_input_stream_new_from_data (data, size, g_free);
	} else if (item->io_started) {


		return;
	} else {


		istream = g_memory_input_stream_new ();
	}

	async_send_request_return_result (item, istream, error);
}
