_run_commands(void)
{
	int d = hold_until - get_time();
	if(labs(d) > 1000)
		hold_until = get_time();
	else if(d > 0)
		return;

	while(sfifo_used(&commands) >= sizeof(command_t))
	{
		command_t cmd;
		if(sfifo_read(&commands, &cmd, (unsigned)sizeof(cmd)) < 0)
		{
			log_printf(ELOG, "audio.c: Engine failure!\n");
			_audio_running = 0;
			return;
		}
		switch(cmd.action)
		{
		  case CMD_STOP:
			DBG2(log_printf(D3LOG, "%d: CMD_STOP\n", get_time());)
			(void)ce_stop(channeltab + cmd.cid, 0, cmd.tag, 32768);
			break;
		  case CMD_STOP_ALL:
			DBG2(log_printf(D3LOG, "%d: CMD_STOP_ALL\n", get_time());)
			channel_stop_all();
			break;
		  case CMD_PLAY:
			DBG2(log_printf(D3LOG, "%d: CMD_PLAY\n", get_time());)
			(void)ce_start(channeltab + cmd.cid, 0,
					cmd.tag, cmd.arg1, cmd.arg2);
			break;
		  case CMD_CCONTROL:
			DBG2(log_printf(D3LOG, "%d: CMD_CCONTROL\n", get_time());)
			(void)ce_control(channeltab + cmd.cid, 0,
					cmd.tag, cmd.index, cmd.arg1);
			break;
		  case CMD_GCONTROL:
			DBG2(log_printf(D3LOG, "%d: CMD_GCONTROL\n", get_time());)
			acc_group_set((unsigned)cmd.cid, cmd.index, cmd.arg1);
			break;
		  case CMD_MCONTROL:
			DBG2(log_printf(D3LOG, "%d: CMD_MCONTROL\n", get_time());)
			bus_ctl_set((unsigned)cmd.cid, (unsigned)cmd.arg1,
					cmd.index, cmd.arg2);
			break;
		  case CMD_WAIT:
			DBG2(log_printf(D3LOG, "%d: CMD_WAIT", get_time());)
			hold_until = cmd.arg1;
			DBG2(log_printf(D3LOG, " (Holding until %d)\n", hold_until);)
			if(hold_until - get_time() > 0)
				return;
			break;
		}
	}
}
