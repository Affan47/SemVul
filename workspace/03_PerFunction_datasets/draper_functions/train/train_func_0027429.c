hsort(void *base, size_t n, size_t size, hsort_cmp_t *cmp)
{
	register char *p, *q, *base0, *hi;
	register unsigned int gap, g;

	if (n < 2)
		return;

	base0 = (char *)base - size;


	gap = (n >> 1) * size;
	hi = base0 + gap + gap;
	if (n & 1)
		hi += size;


	for ( ; gap != size; gap -= size)
	{


		for (p = base0 + (g = gap); (q = p + g) <= hi; p = q)
		{
			g += g;


			if (q != hi && (*cmp)(q + size, q) > 0)
			{
				q += size;
				g += size;
			}


			if ((*cmp)(p, q) >= 0)
				break;

			swap(p, q, size);
		}
	}


	for ( ; hi != base; hi -= size)
	{


		p = (char *)base;
		for (g = size; (q = p + g) <= hi; p = q)
		{
			g += g;
			if (q != hi && (*cmp)(q + size, q) > 0)
			{
				q += size;
				g += size;
			}

			if ((*cmp)(p, q) >= 0)
				break;

			swap(p, q, size);
		}

		swap((char *)base, hi, size);
	}
}
