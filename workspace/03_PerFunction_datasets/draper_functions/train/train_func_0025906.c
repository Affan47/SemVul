QRinput_insertFNC1Header(QRinput *input)
{
	QRinput_List *entry = NULL;

	if(input->fnc1 == 1) {
		entry = QRinput_List_newEntry(QR_MODE_FNC1FIRST, 0, NULL);
	} else if(input->fnc1 == 2) {
		entry = QRinput_List_newEntry(QR_MODE_FNC1SECOND, 1, &(input->appid));
	}
	if(entry == NULL) {
		return -1;
	}

	if(input->head->mode != QR_MODE_STRUCTURE && input->head->mode != QR_MODE_ECI) {
		entry->next = input->head;
		input->head = entry;
	} else {
		entry->next = input->head->next;
		input->head->next = entry;
	}

	return 0;
}
