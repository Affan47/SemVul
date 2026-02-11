find_handle(struct handle *h, int32_t idx, enum handle_type type)
{
    if (idx == 0)
	return NULL;

    while (h) {
	if (h->idx == idx) {
	    if (type == h->type)
		return h->ptr;
	    errx(1, "monger switched type on handle!");
	}
	h = h->next;
    }
    return NULL;
}
