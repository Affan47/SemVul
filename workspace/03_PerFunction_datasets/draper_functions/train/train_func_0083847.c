GeneralPump2(
	lword& byteCount, bool blockingOutput,
	unsigned long maxTime, bool checkDelimiter, byte delimiter)
{
	m_blockedBySpeedLimit = false;

	if (!GetMaxBytesPerSecond())
	{
		size_t ret = DoPump(byteCount, blockingOutput, maxTime, checkDelimiter, delimiter);
		m_doPumpBlocked = (ret != 0);
		return ret;
	}

	bool forever = (maxTime == INFINITE_TIME);
	unsigned long timeToGo = maxTime;
	Timer timer(Timer::MILLISECONDS, forever);
	lword maxSize = byteCount;
	byteCount = 0;

	timer.StartTimer();

	while (true)
	{
		lword curMaxSize = UnsignedMin(ComputeCurrentTransceiveLimit(), maxSize - byteCount);

		if (curMaxSize || m_doPumpBlocked)
		{
			if (!forever) timeToGo = SaturatingSubtract(maxTime, timer.ElapsedTime());
			size_t ret = DoPump(curMaxSize, blockingOutput, timeToGo, checkDelimiter, delimiter);
			m_doPumpBlocked = (ret != 0);
			if (curMaxSize)
			{
				NoteTransceive(curMaxSize);
				byteCount += curMaxSize;
			}
			if (ret)
				return ret;
		}

		if (maxSize != ULONG_MAX && byteCount >= maxSize)
			break;

		if (!forever)
		{
			timeToGo = SaturatingSubtract(maxTime, timer.ElapsedTime());
			if (!timeToGo)
				break;
		}

		double waitTime = TimeToNextTransceive();
		if (!forever && waitTime > timeToGo)
		{
			m_blockedBySpeedLimit = true;
			break;
		}

		WaitObjectContainer container;
		LimitedBandwidth::GetWaitObjects(container, CallStack("NonblockingSource::GeneralPump2() - speed limit", 0));
		container.Wait((unsigned long)waitTime);
	}

	return 0;
}
