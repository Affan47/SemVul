sort_media_device_entry(const void *a, const void *b)
{
	const struct media_device_entry *md_a = a;
	const struct media_device_entry *md_b = b;
	int cmp;

	cmp = strcmp(md_a->device, md_b->device);
	if (cmp)
		return cmp;
	cmp = (int)md_a->type - (int)md_b->type;
	if (cmp)
		return cmp;

	return strcmp(md_a->node, md_b->node);
}
