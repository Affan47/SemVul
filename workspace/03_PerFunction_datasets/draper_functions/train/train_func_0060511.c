init_match_vars(const char *str, int nranges, int *offsets,
			     Buffer *foreachp)
{
	Buffer varname;
	int cnt;

	for (cnt=0; cnt<nranges; cnt++)
	{
		varname="MATCH";
		if (cnt)
			varname.append((unsigned long)cnt);


		Buffer v;

		int i, j;

		i=offsets[cnt*2];
		j=offsets[cnt*2+1];

		if (i < j)
		{
			size_t s=j-i;

			char *ptr=(char *)malloc(s+1);
			if (ptr)
			{
				memcpy(ptr, str + i, s);
				ptr[s]=0;
				v=ptr;
				free(ptr);
			}
		}

		if (foreachp)
		{
			*foreachp += v;
			*foreachp += '\0';
		}

		SetVar(varname, v);
	}
}
