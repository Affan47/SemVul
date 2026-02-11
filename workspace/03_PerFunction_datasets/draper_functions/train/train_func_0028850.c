LogStreamerMain(logstreamer_param *param)
{
	if (!ReceiveXlogStream(param->bgconn, param->startptr, param->timeline,
						   param->sysidentifier, param->xlogdir,
						   reached_end_position, standby_message_timeout,
						   NULL, false, true))


		return 1;

	PQfinish(param->bgconn);
	return 0;
}
