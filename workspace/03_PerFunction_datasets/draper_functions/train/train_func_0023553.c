QRinput_createBitStream(QRinput *input)
{
	QRinput_List *list;
	int bits, total = 0;

	list = input->head;
	while(list != NULL) {
		bits = QRinput_encodeBitStream(list, input->version);
		if(bits < 0) return -1;
		total += bits;
		list = list->next;
	}

	return total;
}
