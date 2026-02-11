ubcsp_put_slip_uart (uint8 ch)
{


	if (ch == SLIP_FRAME)
	{
		put_uart (SLIP_ESCAPE);
		ubcsp_config.send_slip_escape = SLIP_ESCAPE_FRAME;
	}
	else if (ch == SLIP_ESCAPE)
	{
		put_uart (SLIP_ESCAPE);
		ubcsp_config.send_slip_escape = SLIP_ESCAPE_ESCAPE;
	}
	else
	{


		put_uart (ch);
	}
}
