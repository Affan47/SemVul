BufferedReaderPop(WiggleIterator * wi, BufferedReaderData * data) {
	if (wi->done)
		return;
	else if (data->blockData == NULL) {
		wi->done = true;
		return;
	} else if (data->readIndex == data->blockData->count) {
		waitForNextBlock(data);
		goToNextBlock(data);
		if (data->blockData == NULL) {
			killBufferedReader(data);
			wi->done = true;
			return;
		}
	}

	int index = data->readIndex;
	wi->chrom = data->blockData->chrom[index];
	wi->start = data->blockData->start[index];
	wi->finish = data->blockData->finish[index];
	wi->value = (double) data->blockData->value[index];
	data->readIndex++;
}
