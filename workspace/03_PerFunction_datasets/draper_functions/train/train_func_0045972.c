tms5220_status_read(void)
{
	if (RDB_flag)
	{
		RDB_flag = FALSE;
		return(data_register);
	}
	else
	{


		set_interrupt_state(0);

		if (DEBUG_5220) logerror("Status read: TS=%d BL=%d BE=%d\n", talk_status, buffer_low, buffer_empty);

		return (talk_status << 7) | (buffer_low << 6) | (buffer_empty << 5);
	}
}
