r8712_get_rateset_len(u8 *rateset)
{
	uint i = 0;

	while (1) {
		if ((rateset[i]) == 0)
			break;
		if (i > 12)
			break;
		i++;
	}
	return i;
}
