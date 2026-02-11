_nls_malloc(size_t size, const char *type, nls_free_op free_op)
{
	nls_mem *mem = malloc(size + sizeof(nls_mem));

	if (!mem) {
		return NULL;
	}
	nls_mem_alloc_cnt++;
	mem->nm_magic = NLS_MAGIC_MEMCHUNK;
	mem->nm_type = type;
	mem->nm_ref  = 0;
	mem->nm_size = size;
	mem->nm_free_op = free_op;
	nls_mem_chain_add(mem);

	return ++mem;
}
