set_select(struct tca6507_chip *tca, int led, int val)
{
	int mask = (1 << led);
	int bit;

	for (bit = 0; bit < 3; bit++) {
		int n = tca->reg_file[bit] & ~mask;
		if (val & (1 << bit))
			n |= mask;
		if (tca->reg_file[bit] != n) {
			tca->reg_file[bit] = n;
			tca->reg_set |= (1 << bit);
		}
	}
}
