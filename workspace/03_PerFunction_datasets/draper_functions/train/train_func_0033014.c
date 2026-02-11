LogWiggleIterator(WiggleIterator * i, double s) {
	LogWiggleIteratorData * data = (LogWiggleIteratorData *) calloc(1, sizeof(LogWiggleIteratorData));
	data->iter = NonOverlappingWiggleIterator(i);
	data->base = s;
	data->baseLog = log(s);
	double default_value;
	if (!isnan(i->default_value) && i->default_value > 0)
		default_value =  log(i->default_value) / data->baseLog;
	else
		default_value = NAN;
	return newWiggleIterator(data, &LogWiggleIteratorPop, &LogWiggleIteratorSeek, default_value);
}
