List_MoveB ( menulist_s *l, int moy, int my)
{
	int y = l->generic.y + l->generic.parent->y + MLIST_BSIZE;
	int height = l->height - (MLIST_BSIZE * 2);
	int numItems = l->count;
	int maxItems = l->maxItems;
	int count;
	static double remainders = 0;

	if(!my)
		return;

	clamp(maxItems, 0, numItems);

	if(moy <= y+2)
	{
		l->prestep = 0;
		remainders = 0;
		return;
	} else if (moy >= y+height-2) {
		l->prestep = l->count - maxItems;
		remainders = 0;
		return;
	}

	remainders += (double)numItems/100 * ((double)my / (double)height * 100);
	count = (int)remainders;
	remainders -= count;

	l->prestep += count;

	clamp(l->prestep, 0, l->count - maxItems);

}
