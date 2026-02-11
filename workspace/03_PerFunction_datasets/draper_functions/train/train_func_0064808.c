bgzf_seek(BGZF* fp, int64_t pos, int where)
{
	int block_offset;
	int64_t block_address;

	if (fp->is_write || where != SEEK_SET) {
		fp->errcode |= BGZF_ERR_MISUSE;
		return -1;
	}
	block_offset = pos & 0xFFFF;
	block_address = pos >> 16;
	if (_bgzf_seek(fp->fp, block_address, SEEK_SET) < 0) {
		fp->errcode |= BGZF_ERR_IO;
		return -1;
	}
	fp->block_length = 0;
	fp->block_address = block_address;
	fp->block_offset = block_offset;
	return 0;
}
