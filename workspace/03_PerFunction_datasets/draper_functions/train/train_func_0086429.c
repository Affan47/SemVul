buffer_free(struct buffer_info *type) {
	if (!type || !type->data)
		return;

	buffers_destroy(&(type->data));

	type->last	= NULL;
	type->count	= 0;
}
