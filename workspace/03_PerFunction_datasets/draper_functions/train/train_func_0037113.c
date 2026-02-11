open(const char *name)
{
	unsigned char b[16];
	int sz,r;


	close();

	bitch(BITCHINFO,"Opening key storage %s",name);
	bitch_indent();

	fd = ::open(name,O_RDWR | O_BINARY,0644);
	if (fd < 0) {
		if (errno == ENOENT) {
			bitch(BITCHINFO,"File does not exist, creating key storage");
			fd = ::open(name,O_RDWR | O_CREAT | O_BINARY,0644);
			if (fd < 0) {
				bitch(BITCHWARNING,"Cannot create key storage!");
				goto common_exit;
			}

			if (lseek(fd,0,SEEK_SET) != 0) {
				bitch(BITCHWARNING,"Cannot lseek(0) (is this even a file?)");
				goto common_exit_fd;
			}


			write(fd,KeyHeader,8);


			write(fd,LeHe32bin(0),4);


			write(fd,LeHe32bin(24),4);
		}
		else {
			bitch(BITCHWARNING,"Cannot open key storage (%s)",strerror(errno));
			goto common_exit;
		}
	}

	if (lseek(fd,0,SEEK_SET) != 0) {
		bitch(BITCHWARNING,"Cannot lseek(0) (is this even a file?)");
		goto common_exit_fd;
	}

	sz = lseek(fd,0,SEEK_END);
	if (sz < 16) {
		bitch(BITCHWARNING,"File too small or error seeking to end");
		goto common_exit_fd;
	}

	if (lseek(fd,0,SEEK_SET) != 0) {
		bitch(BITCHWARNING,"Cannot lseek(0) second time");
		goto common_exit_fd;
	}

	if ((r=read(fd,b,16)) < 16) {
		bitch(BITCHWARNING,"Cannot read header (only got %u bytes)",r);
		goto common_exit_fd;
	}

	if (memcmp(b,KeyHeader,8)) {
		bitch(BITCHWARNING,"Invalid key storage header");
		goto common_exit_fd;
	}

	root =		binLeHe32(b +  8);
	blocksize =	binLeHe32(b + 12);

	if (blocksize < 24 || blocksize > 512) {
		bitch(BITCHWARNING,"Illegal block size %u",blocksize);
		goto common_exit_fd;
	}

	max_block = (sz - 16) / blocksize;
	bitch(BITCHINFO,"Key storage has %u blocks, root at block %u, %u bytes/block",max_block,root,blocksize);

	if (	(root >= max_block && max_block != 0) ||
		(root != 0         && max_block == 0)) {
		bitch(BITCHWARNING,"Illegal root node value %u",root);
		goto common_exit_fd;
	}

	bitch_unindent();
	return 0;

common_exit_fd:	::close(fd);
common_exit:	bitch_unindent();
	return -1;
}
