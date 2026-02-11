MinReductionPop(WiggleIterator * wi) {
	int i;

	if (wi->done)
		return;

	WiggleReducerData * data = (WiggleReducerData *) wi->data;
	Multiplexer * multi = data->multi;

	if (multi->done) {
		wi->done = true;
		return;
	}

	wi->chrom = multi->chrom;
	wi->start = multi->start;
	wi->finish = multi->finish;
	if (multi->inplay[0])
		wi->value = multi->values[0];
	else
		wi->value = 0;

	if (isnan(wi->value)) {
		popMultiplexer(multi);
		return;
	}

	for (i = 1; i < multi->count; i++) {
		double value;
		if (multi->inplay[i])
			value = multi->values[i];
		else
			value = multi->default_values[i];

		if (isnan(value)) {
			wi->value = NAN;
			break;
		}

		if (wi->value > value)
			wi->value = value;
	}
	popMultiplexer(multi);
}
