ap_message_send(int fd, ap_message_t *msg)
{
	int c;
	ap_key_t *current;

	if (!msg)
		return 0;

	msg->header.version = AP_CONTROL_VERSION;
	if (write (fd, msg, sizeof (ap_message_t)) != sizeof (ap_message_t))
		return 0;

	for (c = 0, current = msg->root; c < msg->header.nr_keys; c++,
			current = current->next) {
		if (current == NULL) {
			fprintf(stderr, "problem!\n");
			continue;
		}
		if (write(fd, current, sizeof(ap_key_t)) != sizeof(ap_key_t)) {
			fprintf(stderr, "error writing key\n");
			continue;
		}
		if (write(fd, current->data, current->length) != current->length) {
			fprintf(stderr, "error writing key data\n");
			continue;
		}
	}

	return 1;
}
