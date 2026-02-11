meson_spifc_fill_buffer(struct meson_spifc *spifc, const u8 *buf,
				    int len)
{
	u32 data;
	int i = 0;

	while (i < len) {
		if (len - i >= 4)
			data = *(u32 *)buf;
		else
			memcpy(&data, buf, len - i);

		regmap_write(spifc->regmap, REG_C0 + i, data);

		buf += 4;
		i += 4;
	}
}
