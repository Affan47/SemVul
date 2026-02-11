send_batch (SearchThreadData *data)
{
	SearchHits *hits;

	data->n_processed_files = 0;

	if (data->uri_hits) {
		hits = g_new (SearchHits, 1);
		hits->uris = data->uri_hits;
		hits->thread_data = data;
		g_idle_add (search_thread_add_hits_idle, hits);
	}
	data->uri_hits = NULL;
}
