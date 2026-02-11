sizeOfSector(struct params *fd, int i)
{
	int j;

	if(i < 0)
		return -1;

	for(j = MAX_SIZECODE-1; j >= 0 && fd->last_sect[j] <= i; j--);
	return j;
}
