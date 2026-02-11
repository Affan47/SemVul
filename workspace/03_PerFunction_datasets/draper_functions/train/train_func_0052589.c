is_route (char *fbbs)
{
	int i;

	for (i = 0; i < NBMASK; i++)
		if (fbbs[i])
			return (1);
	return (0);
}
