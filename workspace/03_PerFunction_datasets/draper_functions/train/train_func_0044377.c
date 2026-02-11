startTimer()
	{
		++VirtualTimerStopCounter;

		if (!isStopped())
		{

			setTime(LastVirtualTime);
		}
	}
