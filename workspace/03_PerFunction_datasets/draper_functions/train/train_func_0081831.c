silly_cmp_tsvector(const TSVector a, const TSVector b)
{
	if (VARSIZE(a) < VARSIZE(b))
		return -1;
	else if (VARSIZE(a) > VARSIZE(b))
		return 1;
	else if (a->size < b->size)
		return -1;
	else if (a->size > b->size)
		return 1;
	else
	{
		WordEntry  *aptr = ARRPTR(a);
		WordEntry  *bptr = ARRPTR(b);
		int			i = 0;
		int			res;


		for (i = 0; i < a->size; i++)
		{
			if (aptr->haspos != bptr->haspos)
			{
				return (aptr->haspos > bptr->haspos) ? -1 : 1;
			}
			else if (aptr->len != bptr->len)
			{
				return (aptr->len > bptr->len) ? -1 : 1;
			}
			else if ((res = strncmp(STRPTR(a) + aptr->pos, STRPTR(b) + bptr->pos, bptr->len)) != 0)
			{
				return res;
			}
			else if (aptr->haspos)
			{
				WordEntryPos *ap = POSDATAPTR(a, aptr);
				WordEntryPos *bp = POSDATAPTR(b, bptr);
				int			j;

				if (POSDATALEN(a, aptr) != POSDATALEN(b, bptr))
					return (POSDATALEN(a, aptr) > POSDATALEN(b, bptr)) ? -1 : 1;

				for (j = 0; j < POSDATALEN(a, aptr); j++)
				{
					if (WEP_GETPOS(*ap) != WEP_GETPOS(*bp))
					{
						return (WEP_GETPOS(*ap) > WEP_GETPOS(*bp)) ? -1 : 1;
					}
					else if (WEP_GETWEIGHT(*ap) != WEP_GETWEIGHT(*bp))
					{
						return (WEP_GETWEIGHT(*ap) > WEP_GETWEIGHT(*bp)) ? -1 : 1;
					}
					ap++, bp++;
				}
			}

			aptr++;
			bptr++;
		}
	}

	return 0;
}
