bgzf_write_init(int compress_level)
{
	BGZF *fp;
	fp = (BGZF*)calloc(1, sizeof(BGZF));
	fp->is_write = 1;
    if ( compress_level==-2 )
    {
        fp->is_compressed = 0;
        return fp;
    }
    fp->is_compressed = 1;
	fp->uncompressed_block = malloc(BGZF_MAX_BLOCK_SIZE);
	fp->compressed_block = malloc(BGZF_MAX_BLOCK_SIZE);
	fp->compress_level = compress_level < 0? Z_DEFAULT_COMPRESSION : compress_level;
	if (fp->compress_level > 9) fp->compress_level = Z_DEFAULT_COMPRESSION;
	return fp;
}
