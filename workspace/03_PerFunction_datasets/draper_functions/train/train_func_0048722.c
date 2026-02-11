CMD_Schedule(F_CMD_ARGS)
{
	Window xw;
	Time time;
	Time current_time;
	char *taction;
	char *token;
	char *next;
	int ms;
	int id;
	int *pid;
	int n;
	FvwmWindow * const fw = exc->w.fw;
	Bool is_periodic = False;

	token = PeekToken(action, &next);
	if (token && strcasecmp(token, "periodic") == 0)
	{
		is_periodic = True;
		action = next;
	}

	n = GetIntegerArguments(action, &action, &ms, 1);
	if (n <= 0)
	{
		fvwm_msg(ERR, "CMD_Schedule",
			 "Requires time to schedule as argument");
		return;
	}
	if (ms < 0)
	{
		ms = 0;
	}
#if 0

	current_time = get_server_time();
#else


	current_time = fev_get_evtime();
#endif
	time = current_time + (Time)ms;

	n = GetIntegerArgumentsAnyBase(action, &taction, &id, 1);
	if (n >= 1)
	{
		pid = &id;
		action = taction;
	}
	else
	{
		pid = NULL;
	}

	if (fw != NULL)
	{
		xw = FW_W(fw);
	}
	else
	{
		xw = None;
	}

	schedule(xw, action, time, pid, (is_periodic == True ? ms : 0));

	return;
}
