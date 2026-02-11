jpeg_check_photoshop_8bim(cli_ctx *ctx, off_t *off)
{
	const unsigned char *buf;
	uint16_t ntmp;
	uint8_t nlength, id[2];
	uint32_t size;
	off_t offset = *off;
	int retval;
	fmap_t *map = *ctx->fmap;

	if(!(buf = fmap_need_off_once(map, offset, 4 + 2 + 1))) {
		cli_dbgmsg("read bim failed\n");
		return -1;
	}
	if (memcmp(buf, "8BIM", 4) != 0) {
		cli_dbgmsg("missed 8bim\n");
		return -1;
	}

	id[0] = (uint8_t)buf[4];
        id[1] = (uint8_t)buf[5];
	cli_dbgmsg("ID: 0x%.2x%.2x\n", id[0], id[1]);
	nlength = buf[6];
	ntmp = nlength + ((((uint16_t)nlength)+1) & 0x01);
	offset += 4 + 2 + 1 + ntmp;

	if (fmap_readn(map, &size, offset, 4) != 4) {
		return -1;
	}
	size = special_endian_convert_32(size);
	if (size == 0) {
		return -1;
	}
	if ((size & 0x01) == 1) {
		size++;
	}

	*off = offset + 4 + size;

	if ((id[0] == 0x04) && ((id[1] == 0x09) || (id[1] == 0x0c))) {

		cli_dbgmsg("found thumbnail\n");
	}
	else {

		return 0;
	}


	offset += 4 + 28;

	retval = cli_check_jpeg_exploit(ctx, offset);
	if (retval == 1) {
		cli_dbgmsg("Exploit found in thumbnail\n");
	}
	return retval;
}
