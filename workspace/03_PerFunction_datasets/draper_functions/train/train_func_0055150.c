memfile_free_mem(MEMFILE * f)
{
    LOG_MEMFILE_BLK *bp, *tmpbp;

#ifdef DEBUG

    if (tot_raw > 100) {
        if (tot_raw > 0xFFFFFFFF)
            if_debug4m(':', f->memory, "[:]tot_raw=%lu%0lu, tot_compressed=%lu%0lu\n",
                       tot_raw >> 32, tot_raw & 0xFFFFFFFF,
                       tot_compressed >> 32, tot_compressed & 0xFFFFFFFF);
         else
            if_debug2m(':', f->memory, "[:]tot_raw=%lu, tot_compressed=%lu\n",
                       tot_raw, tot_compressed);
    }
    if (tot_cache_hits != 0) {
        if_debug3m(':', f->memory, "[:]Cache hits=%lu, cache misses=%lu, swapouts=%lu\n",
                   tot_cache_hits,
                   (long)(tot_cache_miss - (f->log_length / MEMFILE_DATA_SIZE)),
                   tot_swap_out);
    }
    tot_raw = 0;
    tot_compressed = 0;
    tot_cache_hits = 0;
    tot_cache_miss = 0;
    tot_swap_out = 0;
#endif


    bp = f->log_head;

    if (bp != NULL) {

        PHYS_MEMFILE_BLK *pphys = bp->phys_blk;

        {
            for (tmpbp = bp; tmpbp != NULL; tmpbp = tmpbp->link)
                if (tmpbp->phys_blk->data_limit != NULL)
                    tmpbp->phys_blk = 0;
        }

        if (pphys->data_limit != NULL) {

            while (pphys != NULL) {
                PHYS_MEMFILE_BLK *tmpphys = pphys->link;

                FREE(f, pphys, "memfile_free_mem(pphys)");
                pphys = tmpphys;
            }
        }
    }

    while (bp != NULL) {
        if (bp->phys_blk != NULL) {
            FREE(f, bp->phys_blk, "memfile_free_mem(phys_blk)");
        }
        tmpbp = bp->link;
        FREE(f, bp, "memfile_free_mem(log_blk)");
        bp = tmpbp;
    }

    f->log_head = NULL;


    if (f->compressor_initialized) {
        if (f->decompress_state->templat->release != 0)
            (*f->decompress_state->templat->release) (f->decompress_state);
        if (f->compress_state->templat->release != 0)
            (*f->compress_state->templat->release) (f->compress_state);
        f->compressor_initialized = false;
    }

    while (f->raw_head != NULL) {
        RAW_BUFFER *tmpraw = f->raw_head->fwd;

        FREE(f, f->raw_head, "memfile_free_mem(raw)");
        f->raw_head = tmpraw;
    }
}
