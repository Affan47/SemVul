bamCacheBlock(AjPSeqBamBgzf fp, int size)
{
    BamPCache p;
    BamPCache oldp;

    if(AJSEQBAM_MAX_BLOCK_SIZE >= fp->cache_size)
        return;

    if((ajint) ajTableGetLength(fp->cache) * AJSEQBAM_MAX_BLOCK_SIZE >
       fp->cache_size)
    {


    }

    AJNEW0(p);
    p->size = fp->block_length;
    p->end_offset = fp->block_address + size;
    p->block = malloc(AJSEQBAM_MAX_BLOCK_SIZE);
    memcpy(p->block, fp->uncompressed_block, AJSEQBAM_MAX_BLOCK_SIZE);
    oldp = ajTablePut(fp->cache, &fp->block_address, p);

    if(oldp)
    {
        AJFREE(oldp->block);
        AJFREE(oldp);
    }

    return;
}
