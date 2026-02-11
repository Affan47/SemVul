OneacGetResponse (char* chBuff, const int BuffSize, int ExpectedCount)
{
	int Retries = 10;
	int return_val;

	do
	{
		return_val = ser_get_line(upsfd, chBuff, BuffSize, ENDCHAR, IGNCHARS,
																	SECS, USEC);

		if (return_val == ExpectedCount)
			break;

		upsdebugx (3,"!OneacGetResponse retry (%d, %d)...", return_val,Retries);

	} while (--Retries > 0);

	upsdebugx (4,"OneacGetResponse buffer: %s",chBuff);

	if (Retries == 0)
	{
		upsdebugx (2,"!!OneacGetResponse timeout...");
		return_val = 1;
	}
	else
	{
		if (Retries < 10)
			upsdebugx (2,"OneacGetResponse recovered (%d)...", Retries);

		return_val = 0;
	}

    return return_val;
}
