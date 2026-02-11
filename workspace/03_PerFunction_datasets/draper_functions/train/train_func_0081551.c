invert(GB_IMAGE img, int channels)
{
  uint np;
  uint *p;
	bool inv;
	uint mask;
	uint i;

	get_info(img, &p, NULL, NULL, &np, &inv);

	if (!inv)
		mask = RGBA((channels & Red) ? 0xFF : 0, (channels & Green) ? 0xFF : 0, (channels & Blue) ? 0xFF : 0, 0);
	else
		mask = RGBA((channels & Blue) ? 0xFF : 0, (channels & Green) ? 0xFF : 0, (channels & Red) ? 0xFF : 0, 0);

	for (i = 0; i < np; i++)
		p[i] ^= mask;
}
