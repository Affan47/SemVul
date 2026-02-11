_e2_task_backend_parse_flags (gchar *tmp1,
	mode_t *setmask, mode_t *clearmask)
{
	gint shifter;
	switch (tmp1[0])
	{
		case 'g':
			shifter=3;
			break;
		case 'u':
			shifter=6;
			break;
		case 'o':
		default:
			shifter=0;
			break;
	}
	gint mask=0;
	switch (tmp1[2])
	{
		case  'r':
			mask=S_IROTH;
			break;
		case  'w':
			mask=S_IWOTH;
			break;
		case  'x':
			mask=S_IXOTH;
			break;
		case  's':
			if (tmp1[0] == 'u')
				mask=S_IROTH;
			else if (tmp1[0] == 'g')
				mask=S_IWOTH;
			break;
		case  't':
			mask=S_IXOTH;
			shifter = 9;
			break;
		default:
			break;
	}
	if (tmp1[1] == '+')
		*setmask |= mask << shifter;
	else if (tmp1[1] == '-')
		*clearmask	|= mask << shifter;
}
