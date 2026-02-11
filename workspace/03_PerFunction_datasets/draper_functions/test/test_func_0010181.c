fs_memdup(const void * mem, unsigned int byte_size) {
    void * new_mem;

    if (mem) {
        new_mem = malloc(byte_size);
        memcpy(new_mem, mem, byte_size);
    }
    else {
        new_mem = NULL;
    }

    return new_mem;
}
