printToFile(void * args) {
	TeeWiggleIteratorData * data = (TeeWiggleIteratorData *) args;


	pthread_mutex_lock(&data->continue_mutex);
	if (data->count == 0 && !data->done)
		pthread_cond_wait(&data->continue_cond, &data->continue_mutex);
	pthread_mutex_unlock(&data->continue_mutex);

	if (data->count < 0)
		return NULL;

	while(data->dataBlocks) {
		printBlock(data->infile, data->outfile, data->dataBlocks);
		if (goToNextBlock(data))
			return NULL;
	}
	return NULL;
}
