S_PickChannel(int entnum, int entchannel)
{
    int			ch_idx;
    int			first_to_die = -1;
    int			life_left = 0x7fffffff;
	channel_t	*ch;

	if (entchannel < 0)
		Com_Error(ERR_DROP, "S_PickChannel: entchannel < 0");


    for (ch_idx=0 ; ch_idx < MAX_CHANNELS ; ch_idx++)
    {
		if (entchannel != 0
		&& channels[ch_idx].entnum == entnum
		&& channels[ch_idx].entchannel == entchannel)
		{
			first_to_die = ch_idx;
			break;
		}


		if (channels[ch_idx].entnum == cl.playernum+1 && entnum != cl.playernum+1 && channels[ch_idx].sfx)
			continue;

		if (channels[ch_idx].end - paintedtime < life_left)
		{
			life_left = channels[ch_idx].end - paintedtime;
			first_to_die = ch_idx;
		}
   }

	if (first_to_die == -1)
		return NULL;

	ch = &channels[first_to_die];
	memset (ch, 0, sizeof(*ch));

    return ch;
}
