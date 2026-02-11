ff_free(void *ptr, size_t size)
{
    int i;
    size_t chunks, pos;

	dump_free_mem();


    chunks = size_to_chunks(size);

#ifdef DEBUG
    fprintf(stderr, "%u (%u chunks) freizugeben.\n",
            (unsigned)size,
            (unsigned)chunks);
#endif


    pos = ((char *)ptr - mem_pool) / CHUNK_SIZE;

#ifdef DEBUG
    fprintf(stderr, "Freigeben: Ab Chunk %d\n", (int)pos);
#endif


    for (i=pos; i<pos+chunks; ++i)
        clear_bit(free_list, i);
}
