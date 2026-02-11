mono_code_manager_invalidate (MonoCodeManager *cman)
{
	CodeChunk *chunk;

#if defined(__i386__) || defined(__x86_64__)
	int fill_value = 0xcc;
#else
	int fill_value = 0x2a;
#endif

	for (chunk = cman->current; chunk; chunk = chunk->next)
		memset (chunk->data, fill_value, chunk->size);
	for (chunk = cman->full; chunk; chunk = chunk->next)
		memset (chunk->data, fill_value, chunk->size);
}
