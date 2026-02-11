QRinput_List_dup(QRinput_List *entry)
{
	QRinput_List *n;

	n = (QRinput_List *)malloc(sizeof(QRinput_List));
	if(n == NULL) return NULL;

	n->mode = entry->mode;
	n->size = entry->size;
	n->data = (unsigned char *)malloc(n->size);
	if(n->data == NULL) {
		free(n);
		return NULL;
	}
	memcpy(n->data, entry->data, entry->size);
	n->bstream = NULL;
	n->next = NULL;

	return n;
}
