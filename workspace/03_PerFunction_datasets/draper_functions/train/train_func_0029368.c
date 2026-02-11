Word_EmbeddedCmd()
{

	int embedded_cmd;
	int value;

	do
	{
		embedded_cmd = embedded_list[embedded_read++];
		value = embedded_cmd >> 8;

		switch(embedded_cmd & 0x1f)
		{
		case EMBED_Y:
			option_sayas = value;
			break;

		case EMBED_F:
			option_emphasis = value;
			break;

		case EMBED_B:

			if(value == 0)
				pre_pause = 0;
			else
				pre_pause += value;
			break;
		}
	} while(((embedded_cmd & 0x80) == 0) && (embedded_read < embedded_ix));
}
