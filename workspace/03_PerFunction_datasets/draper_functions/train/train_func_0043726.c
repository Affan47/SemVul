doBeeps()
{
	if (!this->shouldDoSounds())
	{
		return;
	}

	if (Missiontime == 0 || Missiontime == Frametime)
	{

		return;
	}

	if (arrival_beep_snd < 0 &&
		departure_beep_snd < 0 &&
		m_stealth_arrival_snd < 0 &&
		stealth_departure_snd < 0)
	{
		return;
	}

	bool departure_happened = false;
	bool stealth_departure_happened = false;

	bool arrival_happened = false;
	bool stealth_arrival_happened = false;

	for (int i = 0; i < MAX_SHIPS; i++)
	{
		ship * shipp = &Ships[i];

		if (shipp->objnum >= 0)
		{
			if (shipp->radar_visible_since >= 0 || shipp->radar_last_contact >= 0)
			{
				if (shipp->radar_visible_since == Missiontime)
				{
					if (shipp->radar_current_status == DISTORTED)
					{
						stealth_arrival_happened = true;
					}
					else
					{
						arrival_happened = true;
					}
				}
				else if (shipp->radar_visible_since < 0 && shipp->radar_last_contact == Missiontime)
				{
					if (shipp->radar_last_status == DISTORTED)
					{
						stealth_departure_happened = true;
					}
					else
					{
						departure_happened = true;
					}
				}
			}
		}
	}

	if (timestamp_elapsed(arrival_beep_next_check))
	{
		if (arrival_beep_snd >= 0 && arrival_happened)
		{
			snd_play(&Snds[arrival_beep_snd]);

			arrival_beep_next_check = timestamp(arrival_beep_delay);
		}
		else if (m_stealth_arrival_snd >= 0 && stealth_arrival_happened)
		{
			snd_play(&Snds[m_stealth_arrival_snd]);

			arrival_beep_next_check = timestamp(arrival_beep_delay);
		}

	}

	if (timestamp_elapsed(departure_beep_next_check))
	{
		if (departure_beep_snd >= 0 && departure_happened)
		{
			snd_play(&Snds[departure_beep_snd]);

			departure_beep_next_check = timestamp(departure_beep_delay);
		}
		else if (stealth_departure_snd >= 0 && stealth_departure_happened)
		{
			snd_play(&Snds[stealth_departure_snd]);

			departure_beep_next_check = timestamp(departure_beep_delay);
		}
	}
}
