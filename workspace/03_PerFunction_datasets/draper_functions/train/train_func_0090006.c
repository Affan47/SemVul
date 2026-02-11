gc_alloc(ptst_t *ptst, int alloc_id)
{
    gc_t *gc = ptst->gc;
    chunk_t *ch;
    gc_global_t *gc_global = gc->global;

    ch = gc->alloc[alloc_id];
    if ( ch->i == 0 )
    {
        if ( gc->alloc_chunks[alloc_id]++ == 100 )
        {
            gc->alloc_chunks[alloc_id] = 0;
            add_chunks_to_list(ch, gc_global->free_chunks);
            gc->alloc[alloc_id] = ch = get_alloc_chunk(gc, alloc_id);
        }
        else
        {
            chunk_t *och = ch;
            ch = get_alloc_chunk(gc, alloc_id);
            ch->next  = och->next;
            och->next = ch;
            gc->alloc[alloc_id] = ch;
        }
    }

    return ch->blk[--ch->i];
}
