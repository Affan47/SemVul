jpeg_check_photoshop(cli_ctx *ctx, off_t offset)
{
	int retval;
	const unsigned char *buffer;
	off_t old;
	fmap_t *map = *ctx->fmap;

	if(!(buffer = fmap_need_off_once(map, offset, 14))) {
		return 0;
	}

	if (memcmp(buffer, "Photoshop 3.0", 14) != 0) {
		return 0;
	}
	offset += 14;

	cli_dbgmsg("Found Photoshop segment\n");
	do {
		old = offset;
		retval = jpeg_check_photoshop_8bim(ctx, &offset);
		if(offset <= old)
			break;
	} while (retval == 0);

	if (retval == -1) {
		retval = 0;
	}
	return retval;
}
