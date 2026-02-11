decode_sequence(unsigned char *element, int element_len) {

	if (element_len != 2 && element_len != 0) return -1;

	if (!element_len) {
		entity_sequence++;
	}
	else {
		entity_sequence = get16(element);
	}

	lprintf(T_OPENTRAC,"Sequence: %d\r\n",entity_sequence);

	return 0;
}
