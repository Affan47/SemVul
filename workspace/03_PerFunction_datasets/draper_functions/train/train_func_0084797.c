CMD_EdgeScroll(F_CMD_ARGS)
{
	int val1, val2, val1_unit, val2_unit, n;
	char *token;

	n = GetTwoArguments(action, &val1, &val2, &val1_unit, &val2_unit);
	if (n != 2)
	{
		fvwm_msg(
			ERR, "SetEdgeScroll",
			"EdgeScroll requires two arguments");
		return;
	}


	if (val1 >= 1000 && val1_unit != 100)
	{
		val1 /= 1000;
		Scr.flags.do_edge_wrap_x = 1;
	}
	else
	{
		Scr.flags.do_edge_wrap_x = 0;
	}
	if (val2 >= 1000 && val2_unit != 100)
	{
		val2 /= 1000;
		Scr.flags.do_edge_wrap_y = 1;
	}
	else
	{
		Scr.flags.do_edge_wrap_y = 0;
	}

	action=SkipNTokens(action,2);
	token = PeekToken(action, NULL);

	if (token)
	{
		if (StrEquals(token, "wrap"))
		{
			Scr.flags.do_edge_wrap_x = 1;
			Scr.flags.do_edge_wrap_y = 1;
		}
		else if (StrEquals(token, "wrapx"))
		{
			Scr.flags.do_edge_wrap_x = 1;
		}
		else if (StrEquals(token, "wrapy"))
		{
			Scr.flags.do_edge_wrap_y = 1;
		}
	}

	Scr.EdgeScrollX = val1 * val1_unit / 100;
	Scr.EdgeScrollY = val2 * val2_unit / 100;

	checkPanFrames();

	return;
}
