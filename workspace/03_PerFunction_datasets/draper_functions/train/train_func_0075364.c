ext2fs_file_zero_past_offset(ext2_file_t file,
					      ext2_off64_t offset)
{
	ext2_filsys fs = file->fs;
	char *b = NULL;
	ext2_off64_t off = offset % fs->blocksize;
	blk64_t blk;
	int ret_flags;
	errcode_t retval;

	if (off == 0)
		return 0;

	retval = sync_buffer_position(file);
	if (retval)
		return retval;


	retval = ext2fs_bmap2(fs, file->ino, NULL, NULL, 0,
			      offset / fs->blocksize, &ret_flags, &blk);
	if (retval)
		return retval;
	if ((blk == 0) || (ret_flags & BMAP_RET_UNINIT))
		return 0;


	retval = ext2fs_get_mem(fs->blocksize, &b);
	if (retval)
		return retval;


	retval = io_channel_read_blk64(fs->io, blk, 1, b);
	if (retval)
		goto out;

	memset(b + off, 0, fs->blocksize - off);

	retval = io_channel_write_blk64(fs->io, blk, 1, b);
	if (retval)
		goto out;

out:
	ext2fs_free_mem(&b);
	return retval;
}
