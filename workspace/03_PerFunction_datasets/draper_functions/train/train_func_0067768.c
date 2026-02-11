append_to_buffer(void * buffer, long * bufsize, void * chunk, int chunk_size)
{

    buffer=realloc(buffer, (*bufsize)+chunk_size);
    if (buffer)
    {
        memcpy(buffer+(*bufsize), chunk, chunk_size);
        *bufsize+=chunk_size;
    } else {
        fail(4, "Out of memory\n");
    }

    return buffer;
}
