AllocColorset(int n)
{

	if (n < nColorsets)
	{
		return;
	}


	Colorset = (colorset_t *)saferealloc(
		(char *)Colorset, ++n * sizeof(colorset_t));


	if (n == 0)
	{
		memset(
			&Colorset[nColorsets], 0,
			(n - nColorsets) * sizeof(colorset_t));
	}
	else
	{


		for ( ; nColorsets < n; nColorsets++)
		{
			memcpy(
				&Colorset[nColorsets], Colorset,
				sizeof(colorset_t));
		}
	}
	nColorsets = n;

	return;
}
