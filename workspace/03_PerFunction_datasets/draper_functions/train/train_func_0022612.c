Finalize(BitString *b)
{
	if (b == NULL) return CONTAINER_ERROR_BADARG;
	if (b->Flags&CONTAINER_READONLY)
		return ReadOnlyError("Finalize",b);
	b->Allocator->free(b->contents);
	b->Allocator->free(b);
	return 1;
}
