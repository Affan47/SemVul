max17042_get_temperature(struct max17042_chip *chip, int *temp)
{
	int ret;
	u32 data;
	struct regmap *map = chip->regmap;

	ret = regmap_read(map, MAX17042_TEMP, &data);
	if (ret < 0)
		return ret;

	*temp = data;

	if (*temp & 0x8000) {
		*temp = (0x7fff & ~*temp) + 1;
		*temp *= -1;
	}


	*temp = *temp * 10 / 256;
	return 0;
}
