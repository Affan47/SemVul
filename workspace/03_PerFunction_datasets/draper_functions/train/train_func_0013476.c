get_baud(char * szbaud)
{
	speed_spec *s;
	int speed = 0;
	if (szbaud != 0)
	{
		for (s = speeds; s->name; s++)
		{
			if (strcmp(s->name, szbaud) == 0)
			{
				speed = s->flag;
				break;
			}
		}
	}

	if (speed == 0)
		s = &speeds[3];
	log_message(STREAM_MAIN, MSG_GOOD, "Setting speed %s\n", s->name);
	return s->flag;
}
