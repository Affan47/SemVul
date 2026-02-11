cache_contains(Text *txt, Piece *p) {
	Buffer *buf = txt->buffers;
	Action *a = txt->current_action;
	if (!buf || !txt->cache || txt->cache != p || !a || !a->change)
		return false;

	Piece *start = a->change->new.start;
	Piece *end = a->change->new.end;
	bool found = false;
	for (Piece *cur = start; !found; cur = cur->next) {
		if (cur == p)
			found = true;
		if (cur == end)
			break;
	}

	return found && p->data + p->len == buf->data + buf->len;
}
