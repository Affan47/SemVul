TtyEventWait(DISPLAY * display, int milliSeconds)
{
	struct timeval	timeOut;

	if (milliSeconds <= 0)
		return FALSE;

	timeOut.tv_sec = milliSeconds / 1000;
	timeOut.tv_usec = (milliSeconds % 1000) * 1000;

	(void) select(0, NULL, NULL, NULL, &timeOut);

	return FALSE;
}
