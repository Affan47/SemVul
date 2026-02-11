PrintTextRaw (void *xtbuf, unsigned char *text, int indent, time_t stamp)
{
	char *last_text = text;
	int len = 0;
	int beep_done = FALSE;


	while (1)
	{
		switch (*text)
		{
		case 0:
			PrintTextLine (xtbuf, last_text, len, indent, stamp);
			return;
		case '\n':
			PrintTextLine (xtbuf, last_text, len, indent, stamp);
			text++;
			if (*text == 0)
				return;
			last_text = text;
			len = 0;
			break;
		case ATTR_BEEP:
			*text = ' ';
			if (!beep_done)
			{
				beep_done = TRUE;
				if (!prefs.hex_input_filter_beep)
					gdk_beep ();
			}
		default:
			text++;
			len++;
		}
	}
}
