S_PaintChannels(int endtime)
{
	int 	i;
	int 	end;
	channel_t *ch;
	sfxcache_t	*sc;
	int		ltime, count;
	playsound_t	*ps;
	extern qboolean sound_started;

	if (!sound_started)
		return;

	snd_vol = s_volume->value*256;

	while (paintedtime < endtime)
	{

		end = endtime;
		if (endtime - paintedtime > PAINTBUFFER_SIZE)
			end = paintedtime + PAINTBUFFER_SIZE;


		while (1)
		{
			ps = s_pendingplays.next;
			if (ps == &s_pendingplays)
				break;
			if (ps->begin <= paintedtime)
			{
				S_IssuePlaysound (ps);
				continue;
			}

			if (ps->begin < end)
				end = ps->begin;
			break;
		}


		if (s_rawend < paintedtime)
		{
			memset(paintbuffer, 0, (end - paintedtime) * sizeof(portable_samplepair_t));
		}
		else
		{
			int		s;
			int		stop;

			stop = (end < s_rawend) ? end : s_rawend;

			for (i=paintedtime ; i<stop ; i++)
			{
				s = i&(MAX_RAW_SAMPLES-1);
				paintbuffer[i-paintedtime] = s_rawsamples[s];
			}

			for ( ; i<end ; i++)
			{
				paintbuffer[i-paintedtime].left = 0;
				paintbuffer[i-paintedtime].right = 0;
			}
		}


		ch = channels;
		for (i=0; i<MAX_CHANNELS ; i++, ch++)
		{
			ltime = paintedtime;

			while (ltime < end)
			{
				if (!ch->sfx || (!ch->leftvol && !ch->rightvol) )
					break;


				count = end - ltime;


				if (ch->end < end)
					count = ch->end - ltime;

				sc = S_LoadSound (ch->sfx);
				if (!sc)
					break;

				if (count > 0 && ch->sfx)
				{
					if (sc->width == 1)
						S_PaintChannelFrom8(ch, sc, count,  ltime - paintedtime);
					else
						S_PaintChannelFrom16(ch, sc, count, ltime - paintedtime);

					ltime += count;
				}


				if (ltime >= ch->end)
				{
					if (ch->autosound)
					{
						ch->pos = 0;
						ch->end = ltime + sc->length;
					}
					else if (sc->loopstart >= 0)
					{
						ch->pos = sc->loopstart;
						ch->end = ltime + sc->length - ch->pos;
					}
					else
					{
						ch->sfx = NULL;
					}
				}
			}

		}


		S_TransferPaintBuffer(end);
		paintedtime = end;
	}
}
