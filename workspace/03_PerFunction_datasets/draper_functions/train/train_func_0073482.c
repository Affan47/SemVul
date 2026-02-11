saturate(int *i, int minv, int maxv)
{
	if (*i < minv)
		*i = minv;
	else if (*i > maxv)
		*i = maxv;
}
