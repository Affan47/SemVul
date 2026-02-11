_AddVoteMenu (edict_t * ent, int fromix)
{
  int i = 0, j = 0;
  qboolean erg = true;

	while (i < xvlistsize && erg == true)
	{
		if (xvotelist[i].VoteTitle && xvotelist[i].DependsOn->value
		&& xvotelist[i].VoteSelected)
		{
			if (j >= fromix)
			{
				erg = xMenu_Add(ent, xvotelist[i].VoteTitle,
								xvotelist[i].VoteSelected);
			}
			j++;
		}
		i++;
	}
}
