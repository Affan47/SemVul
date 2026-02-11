dotruncate(unsigned size)
{
	int oldsize = file_size;
	int ret;

	size -= size % truncbdy;
	if (size > biggest) {
		biggest = size;
		if (!quiet && testcalls > simulatedopcount)
			prt("truncating to largest ever: 0x%x\n", size);
	}

	log4(OP_TRUNCATE, size, (unsigned)file_size, 0);

	if (size > file_size)
		memset(good_buf + file_size, '\0', size - file_size);
	else if (size < file_size)
		memset(good_buf + size, '\0', file_size - size);
	file_size = size;

	if (testcalls <= simulatedopcount)
		return;

	if ((progressinterval && testcalls % progressinterval == 0) ||
	    (debug && (monitorstart == -1 || monitorend == -1 ||
		      size <= monitorend)))
		prt("%lu trunc\tfrom 0x%x to 0x%x\n", testcalls, oldsize, size);
	if ((ret = rbd_resize(image, size)) < 0) {
		prt("rbd_resize: %x\n", size);
		prterrcode("dotruncate: ftruncate", ret);
		report_failure(160);
	}
}
