same(const unsigned char *new,
			 const unsigned char *old,
			 unsigned int length)
{
	unsigned int i;

	for (i = 0; i < length; i++) {
		if (new[i] != old[i])
			break;
	}
	return i;
}
