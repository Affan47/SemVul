killBufferedReader(BufferedReaderData * data) {
	if (data->killed)
		return;

	pthread_mutex_lock(&data->count_mutex);
	data->blockCount = -1;

	pthread_cond_signal(&data->count_cond);
	pthread_mutex_unlock(&data->count_mutex);
	pthread_join(data->downloaderThreadID, NULL);

	pthread_mutex_destroy(&data->count_mutex);
	pthread_cond_destroy(&data->count_cond);

	while (data->blockData) {
		BlockData * prevData = data->blockData;
		data->blockData = data->blockData->next;
		destroyBlockData(prevData);
	}

	data->lastBlockData = NULL;
	data->blockCount = 0;
	data->killed = true;
}
