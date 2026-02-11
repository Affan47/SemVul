regmap_volatile_range(struct regmap *map, unsigned int reg,
	size_t num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		if (!regmap_volatile(map, reg + i))
			return false;

	return true;
}
