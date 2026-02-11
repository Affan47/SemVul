lol_get(
	LOL	*lol,
	int	i )
{
	return i < lol->count ? lol->list[i] : 0;
}
