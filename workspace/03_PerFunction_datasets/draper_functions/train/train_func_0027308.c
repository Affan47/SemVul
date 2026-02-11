QRinput_mergeBitStream(QRinput *input)
{
	BitStream *bstream;
	QRinput_List *list;
	int ret;

	if(QRinput_convertData(input) < 0) {
		return NULL;
	}

	bstream = BitStream_new();
	if(bstream == NULL) return NULL;

	list = input->head;
	while(list != NULL) {
		ret = BitStream_append(bstream, list->bstream);
		if(ret < 0) {
			BitStream_free(bstream);
			return NULL;
		}
		list = list->next;
	}

	return bstream;
}
