ld9040_dcs_write(struct ld9040 *ctx, const u8 *data, size_t len)
{
	int ret = 0;

	if (ctx->error < 0 || len == 0)
		return;

	dev_dbg(ctx->dev, "writing dcs seq: %*ph\n", (int)len, data);
	ret = ld9040_spi_write_word(ctx, *data);

	while (!ret && --len) {
		++data;
		ret = ld9040_spi_write_word(ctx, *data | 0x100);
	}

	if (ret) {
		dev_err(ctx->dev, "error %d writing dcs seq: %*ph\n", ret,
			(int)len, data);
		ctx->error = ret;
	}

	usleep_range(300, 310);
}
