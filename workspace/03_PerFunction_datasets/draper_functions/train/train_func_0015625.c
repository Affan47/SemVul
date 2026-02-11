FF_realloc(FT_Memory memory, long cur_size, long new_size, void *block)
{
    gs_memory_t *mem = (gs_memory_t *) memory->user;
    void *tmp;

    if (cur_size == new_size) {
        return (block);
    }

    tmp = gs_malloc(mem, new_size, 1, "FF_realloc");
    if (tmp && block) {
        memcpy(tmp, block, min(cur_size, new_size));

        gs_free(mem, block, 0, 0, "FF_realloc");
    }

    return (tmp);
}
