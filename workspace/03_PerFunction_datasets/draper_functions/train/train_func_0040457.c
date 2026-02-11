bamCacheLoadBlock(AjPSeqBamBgzf fp, ajlong block_address)
{
	const BamPCache p;

	p = ajTableFetchV(fp->cache, &block_address);

	if(!p)
            return 0;

	if(fp->block_length != 0)
            fp->block_offset = 0;

	fp->block_address = block_address;
	fp->block_length = p->size;
	memcpy(fp->uncompressed_block, p->block, AJSEQBAM_MAX_BLOCK_SIZE);
	fseek(fp->file, p->end_offset, SEEK_SET);

	return p->size;
}
