getblock (uae_u8 *bitmap)
{
	int i = 0;
	while (bitmap[i] != 0xff) {
		if (bitmap[i] == 0) {
			bitmap[i] = 1;
			return i;
		}
		i++;
	}
	return -1;
}
