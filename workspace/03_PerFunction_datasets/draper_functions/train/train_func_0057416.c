ext2fs_write_ext_attr(ext2_filsys fs, blk_t block, void *inbuf)
{
	errcode_t	retval;
	char		*write_buf;
	char		*buf = NULL;

#ifdef WORDS_BIGENDIAN
	retval = ext2fs_get_mem(fs->blocksize, &buf);
	if (retval)
		return retval;
	write_buf = buf;
	ext2fs_swap_ext_attr(buf, inbuf, fs->blocksize, 1);
#else
	write_buf = (char *) inbuf;
#endif
 	retval = io_channel_write_blk(fs->io, block, 1, write_buf);
	if (buf)
		ext2fs_free_mem(&buf);
	if (!retval)
		ext2fs_mark_changed(fs);
	return retval;
}
