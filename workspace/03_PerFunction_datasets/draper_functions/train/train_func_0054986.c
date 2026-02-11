SmoothWiggleIteratorSeek(WiggleIterator * wi, const char * chrom, int start, int finish) {
	SmoothWiggleIteratorData * data = (SmoothWiggleIteratorData *) wi->data;
	seek(data->iter, chrom, start, finish);
	int i;
	for (i = 0; i < data->width; i++)
		data->buffer[i] = 0;
	data->first = 0;
	data->last = 0;
	data->sum = 0;
	data->count = 0;
	wi->done = false;
	pop(wi);
}
