alloc_free_chunk(chunk_t * cp, gs_ref_memory_t * mem)
{
    gs_memory_t *parent = mem->non_gc_memory;
    byte *cdata = (byte *)cp->chead;
    ulong csize = (byte *)cp->cend - cdata;

    alloc_unlink_chunk(cp, mem);
    mem->allocated -= st_chunk.ssize;
    if (mem->cfreed.cp == cp)
        mem->cfreed.cp = 0;
    if (cp->outer == 0) {
        mem->allocated -= csize;
        gs_free_object(parent, cdata, "alloc_free_chunk(data)");
    } else {
        cp->outer->inner_count--;
        gs_alloc_fill(cdata, gs_alloc_fill_free, csize);
    }
    gs_free_object(parent, cp, "alloc_free_chunk(chunk struct)");
}
