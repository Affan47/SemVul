sync_buffer_position(ext2_file_t file)
{
	blk_t	b;
	errcode_t	retval;

	b = file->pos / file->fs->blocksize;
	if (b != file->blockno) {
		retval = ext2fs_file_flush(file);
		if (retval)
			return retval;
		file->flags &= ~EXT2_FILE_BUF_VALID;
	}
	file->blockno = b;
	return 0;
}
