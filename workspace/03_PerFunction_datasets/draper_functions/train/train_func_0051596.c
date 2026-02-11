alloc(size_t size)
{
    void *ptr;

    if(size > free) {
	size_t new_size = (size > block_size? size : block_size);
	block *b = (block *)vaul_xmalloc(sizeof(block) + new_size);

	b->link = blocks;
	blocks = b;
	mem = b->mem;
	free = new_size;
	b->size = 0;
    }
    ptr = mem;
    mem += size;
    free -= size;
    blocks->size += size;

    return ptr;
}
