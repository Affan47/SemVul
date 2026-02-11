autoreverse_diag(int j)
{
	if (spr[j].dir == 0) spr[j].dir = 7;
	int r = ((rand() % 2)+1);

	if ( (spr[j].dir == 1) || (spr[j].dir == 3) )
	{

		if (r == 1)
			return(9);
		if (r == 2)
			return(7);
	}

	if ( (spr[j].dir == 3) || (spr[j].dir == 6) )
	{
		if (r == 1)
			return(7);
		if (r == 2)
			return(1);

	}

    if ( (spr[j].dir == 9) || (spr[j].dir == 8) )
	{
		if (r == 1)
			return(1);
		if (r == 2)
			return(7);
	}

    if ( (spr[j].dir == 7) || (spr[j].dir == 4) )
	{
		if (r == 1)
			return(3);
		if (r == 2)
			return(9);

	}

	log_debug("Auto Reverse Diag was sent a dir %d sprite, base %d walk.",spr[j].dir, spr[j].base_walk);
	return(0);
}
