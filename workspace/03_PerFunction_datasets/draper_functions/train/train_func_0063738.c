Grab(Action *source) {
	delete []data;

	position = source->position;
	at = source->at;
	data = source->data;
	lenData = source->lenData;
	mayCoalesce = source->mayCoalesce;


	source->position = 0;
	source->at = startAction;
	source->data = 0;
	source->lenData = 0;
	source->mayCoalesce = true;
}
