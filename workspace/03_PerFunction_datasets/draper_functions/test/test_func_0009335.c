queue_new_packet(struct pkt **q, int type, void *buf, int len)
{
	struct pkt *new = malloc(sizeof(struct pkt) + len);
	if (!new)
		return -ENOMEM;

	new->type = type;
	new->len = len;
	new->next = NULL;
	memcpy(new->data, buf, len);
	queue_packet(q, new);
	return 0;
}
