dnpds40_main_loop(void *vctx, int copies) {
	struct dnpds40_ctx *ctx = vctx;
	int ret;
	struct dnpds40_cmd cmd;
	uint8_t *resp = NULL;
	int len = 0;

	uint8_t *ptr;
	char buf[9];

	if (!ctx)
		return 1;


	if (copies > 1 && ctx->qty_offset) {
		snprintf(buf, sizeof(buf), "%07d\r", copies);
		memcpy(ctx->qty_offset, buf, 8);


	}

top:

	if (resp) free(resp);


	dnpds40_build_cmd(&cmd, "STATUS", "", 0);
	resp = dnpds40_resp_cmd(ctx, &cmd, &len);
	if (!resp)
		return -1;
	dnpds40_cleanup_string((char*)resp, len);


	if (strcmp("00000", (char*)resp)) {
		if (!strcmp("00001", (char*)resp)) {
			free(resp);

			dnpds40_build_cmd(&cmd, "INFO", "FREE_PBUFFER", 0);
			resp = dnpds40_resp_cmd(ctx, &cmd, &len);
			if (!resp)
				return -1;
			dnpds40_cleanup_string((char*)resp, len);


			if (!strcmp("FBP00", (char*)resp) ||
			    (ctx->buf_needed == 1 && !strcmp("FBP01", (char*)resp))) {
				INFO("Insufficient printer buffers, retrying...\n");
				sleep(1);
				goto top;
			}
		} else if (!strcmp("00500", (char*)resp) ||
			   !strcmp("00510", (char*)resp)) {
			INFO("Printer cooling, retrying...\n");
			sleep(1);
			goto top;
		}
		free(resp);
		ERROR("Printer Status: %s\n", dnpds40_statuses((char*)resp));
		return 1;
	}


	ptr = ctx->databuf;

	while(ptr && ptr < (ctx->databuf + ctx->datalen)) {
		int i;
		buf[8] = 0;
		memcpy(buf, ptr + 24, 8);
		i = atoi(buf) + 32;


		if ((ret = send_data(ctx->dev, ctx->endp_down,
				     ptr, i)))
			return ret;

		ptr += i;
	}


	if (ctx->qty_offset)
		copies = 1;


	if (terminate)
		copies = 1;

	INFO("Print complete (%d copies remaining)\n", copies - 1);

	if (copies && --copies) {
		goto top;
	}

	if (resp) free(resp);

	return 0;
}
