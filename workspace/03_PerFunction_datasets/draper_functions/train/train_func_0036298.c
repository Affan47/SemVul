arena_block_new(size_t len)
{
	struct arena_block *self;

	self		= malloc(sizeof *self + len);
	if (!self)
		return NULL;

	self->free	= self->data;
	self->end	= self->data + len;
	self->next	= NULL;

	return self;
}
