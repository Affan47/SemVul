rdump_symlink(ext2_ino_t ino, struct ext2_inode *inode,
			  const char *fullname)
{
	ext2_file_t e2_file;
	char *buf;
	errcode_t retval;

	buf = malloc(inode->i_size + 1);
	if (!buf) {
		com_err("rdump", errno, "while allocating for symlink");
		goto errout;
	}


	if (inode->i_blocks == 0)
		strcpy(buf, (char *) inode->i_block);
	else {
		unsigned bytes = inode->i_size;
		char *p = buf;
		retval = ext2fs_file_open(current_fs, ino, 0, &e2_file);
		if (retval) {
			com_err("rdump", retval, "while opening symlink");
			goto errout;
		}
		for (;;) {
			unsigned int got;
			retval = ext2fs_file_read(e2_file, p, bytes, &got);
			if (retval) {
				com_err("rdump", retval, "while reading symlink");
				goto errout;
			}
			bytes -= got;
			p += got;
			if (got == 0 || bytes == 0)
				break;
		}
		buf[inode->i_size] = 0;
		retval = ext2fs_file_close(e2_file);
		if (retval)
			com_err("rdump", retval, "while closing symlink");
	}

	if (symlink(buf, fullname) == -1) {
		com_err("rdump", errno, "while creating symlink %s -> %s", buf, fullname);
		goto errout;
	}

errout:
	free(buf);
}
