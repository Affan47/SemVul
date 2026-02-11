prep_recalc (void)
{
	int pnum;
	char *variant;

	if (recalc.mode == '-' ||
		  recalc.mode == 'b' ||
			recalc.mode == 'B' )
		return 1;

	if (recalc.mode == 'p')
	{
		if (strchr(recalc.input, '_'))
		{
			recalc.prefix = pnum2prefix_variant(recalc.input, 0);
		}
		else
		{
			pnum = atoi(recalc.input);
			recalc.prefix = pnum2prefix(pnum, 0);
		}
	}
	else if (recalc.mode == 'v')
	{
		if ( (variant = strchr(recalc.input, '_')) )
		{
			int p;
			char *vbn;
			char s[16];
			variant++;
			for (p=0; p<getNProvider(); p++)
			{
				vbn = getProviderVBN(p);
				if (strncmp(vbn, recalc.input, strlen(vbn)))
					continue;
				pnum = prefix2pnum(p);
				snprintf(s, 12, "%d_%s", pnum, variant );
				if ( (recalc.prefix = pnum2prefix_variant(s, 0)) != UNKNOWN )
					break;
			}
		}
		else
		{
			int l;
			recalc.prefix = vbn2prefix(recalc.input, &l);
		}
	}
	else
	{
		printf("Unknown provider selection mode in option -r: %c.\n", recalc.mode);
		return 0;
	}
	if (recalc.prefix == UNKNOWN)
	{
		printf("No provider found in ratefile for %s %s.\n",
		       (recalc.mode=='p') ? "Pnum" : "VBN", recalc.input);
		return 0;
	}
	return 1;
}
