ipmi_sol_red_pill(struct ipmi_intf * intf)
{
	char   * buffer;
	int    numRead;
	int    bShouldExit       = 0;
	int    bBmcClosedSession = 0;
	fd_set read_fds;
	struct timeval tv;
	int    retval;
	int    buffer_size = intf->session->sol_data.max_inbound_payload_size;
	int    keepAliveRet = 0;
	int    retrySol = 0;

	buffer = (char*)malloc(buffer_size);
	if (buffer == NULL) {
		lprintf(LOG_ERR, "ipmitool: malloc failure");
		return -1;
	}


	gettimeofday(&_start_keepalive, 0);

	enter_raw_mode();

	while (! bShouldExit)
	{
		FD_ZERO(&read_fds);
		FD_SET(0, &read_fds);
		FD_SET(intf->fd, &read_fds);


		if(_use_sol_for_keepalive == 0)
		{
			keepAliveRet = ipmi_sol_keepalive_using_getdeviceid(intf);
		}
		else
		{
			keepAliveRet = ipmi_sol_keepalive_using_sol(intf);
		}

		if (keepAliveRet != 0)
		{


			if (retrySol == MAX_SOL_RETRY)
			{

				bShouldExit = 1;
				continue;
			}
			else
			{
				retrySol++;
			}
		}
		else
		{

			retrySol = 0;
		}


		tv.tv_sec =  0;
		tv.tv_usec = 500000;

		retval = select(intf->fd + 1, &read_fds, NULL, NULL, &tv);

		if (retval)
		{
			if (retval == -1)
			{

				perror("select");
				return -1;
			}


			if (FD_ISSET(0, &read_fds))
	 		{
				bzero(buffer, sizeof(buffer));
				numRead = read(fileno(stdin),
							   buffer,
							   buffer_size);

				if (numRead > 0)
				{
					int rc = processSolUserInput(intf, (uint8_t *)buffer, numRead);

					if (rc)
					{
						if (rc < 0)
							bShouldExit = bBmcClosedSession = 1;
						else
							bShouldExit = 1;
					}
				}
				else
				{
					bShouldExit = 1;
				}
			}


			else if (FD_ISSET(intf->fd, &read_fds))
			{
				struct ipmi_rs * rs =intf->recv_sol(intf);
				if (! rs)
				{
					bShouldExit = bBmcClosedSession = 1;
				}
				else
				{
					output(rs);
				}
 			}


 			else
			{
				lprintf(LOG_ERR, "Error: Select returned with nothing to read");
				bShouldExit = 1;
			}
		}
	}

	leave_raw_mode();

	if (keepAliveRet != 0)
	{
		lprintf(LOG_ERR, "Error: No response to keepalive - Terminating session");

		ipmi_sol_deactivate(intf);
		exit(1);
	}

	if (bBmcClosedSession)
	{
		lprintf(LOG_ERR, "SOL session closed by BMC");
		exit(1);
	}
	else
		ipmi_sol_deactivate(intf);

	return 0;
}
