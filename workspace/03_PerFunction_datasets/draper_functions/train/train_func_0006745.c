QRinput_createBitStream(QRinput *input, BitStream *bstream)
{
	QRinput_List *list;
	int bits, total = 0;

	list = input->head;
	while(list != NULL) {
		bits = QRinput_encodeBitStream(list, bstream, input->version, input->mqr);
		if(bits < 0) return -1;
		total += bits;
		list = list->next;
	}

	return total;
}
