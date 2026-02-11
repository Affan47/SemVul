bitmap_copy(struct bitmap *a, struct bitmap *b)
{
	if(a->width != b->width || a->height != b->height)
		return;
	memcpy(b->data, a->data, a->width * a->height * sizeof(*a->data));
}
