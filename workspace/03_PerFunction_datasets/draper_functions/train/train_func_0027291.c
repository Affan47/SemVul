S_SoundList_f (void)
{
	int		i, count = 0;
	sfx_t	*sfx;
	sfxcache_t	*sc;
	int		size, total = 0;

	for (sfx=known_sfx, i=0 ; i<num_sfx ; i++, sfx++)
	{
		if (!sfx->registration_sequence)
			continue;
		sc = sfx->cache;
		if (sc)
		{
			size = sc->length * sc->width * sc->channels;
			total += size;
			if (sc->loopstart >= 0)
				Com_Printf ("L");
			else
				Com_Printf (" ");
			Com_Printf("(%2db) %6i : %s\n", sc->width*8,  size, sfx->name);
		}
		else
		{
			if (sfx->name[0] == '*')
				Com_Printf("  placeholder : %s\n", sfx->name);
			else
				Com_Printf("  not loaded  : %s\n", sfx->name);
		}
		count++;
	}
	Com_Printf ("%i sounds\n", count);
	Com_Printf ("Total resident: %i\n", total);
}
