invertPixels()
{
	uint i, n;
	uint *p;

	n = width() * height();
	p = (uint *)bits();

	for (i = 0; i < n; i++)
		p[i] ^= 0xFFFFFF;
}
