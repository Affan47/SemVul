write_byte_to_memory_block(memory_block *MB, int32 index, int value)
{   uchar *p; int ch = index/ALLOC_CHUNK_SIZE;
    if (ch < 0)
    {   compiler_error_named("memory: negative index to", chunk_name(MB, 0));
        return;
    }
    if (ch >= 72) fatalerror("One of the memory blocks has exceeded 640K");

    if (MB->chunk[ch] == NULL)
    {   int i;
        MB->chunk[ch] = my_malloc(ALLOC_CHUNK_SIZE, chunk_name(MB, ch));
        p = MB->chunk[ch];
        for (i=0; i<ALLOC_CHUNK_SIZE; i++) p[i] = 255;
    }

    p = MB->chunk[ch];
    p[index % ALLOC_CHUNK_SIZE] = value;
}
