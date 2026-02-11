ProcessMessage(unsigned long type, unsigned long *body)
{
	char *tline;
	int change = 0;
	static Bool is_initial = True;

	switch (type)
	{
	case M_CONFIG_INFO:
		tline = (char*)&(body[3]);
		ExecuteMatchingCommands(ParseConfigLine(tline), EXEC_ALWAYS);
		break;

	case M_NEW_DESK:
		if (is_initial)
		{
			change = EXEC_ALWAYS;
			is_initial = False;
		}
		else if (current_desk != body[0])
		{
			current_desk = body[0];
			change |= EXEC_CHANGED_DESK;
		}
		ExecuteMatchingCommands(-1, change);
		break;

	case M_NEW_PAGE:
		if (is_initial)
		{
			change = EXEC_ALWAYS;
			is_initial = False;
		}
		if (current_desk != body[2])
		{
			current_desk = body[2];
			change |= EXEC_CHANGED_DESK;
		}
		if (current_x != body[0] / MyDisplayWidth ||
		    current_y != body[1] / MyDisplayHeight)
		{
			current_x = body[0] / MyDisplayWidth;
			current_y = body[1] / MyDisplayHeight;
			change |= EXEC_CHANGED_PAGE;
		}
		ExecuteMatchingCommands(-1, change);
		break;

	}
}
