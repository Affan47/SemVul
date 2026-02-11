DoFlush(unsigned long maxTime, size_t targetSize)
{
	NetworkSender &sender = AccessSender();

	bool forever = maxTime == INFINITE_TIME;
	Timer timer(Timer::MILLISECONDS, forever);
	unsigned int totalFlushSize = 0;

	while (true)
	{
		if (m_buffer.CurrentSize() <= targetSize)
			break;

		if (m_needSendResult)
		{
			if (sender.MustWaitForResult() &&
				!sender.Wait(SaturatingSubtract(maxTime, timer.ElapsedTime()),
					CallStack("NetworkSink::DoFlush() - wait send result", 0)))
				break;

			unsigned int sendResult = sender.GetSendResult();
#if CRYPTOPP_TRACE_NETWORK
			OutputDebugString((IntToString((unsigned int)this) + ": Sent " + IntToString(sendResult) + " bytes\n").c_str());
#endif
			m_buffer.Skip(sendResult);
			totalFlushSize += sendResult;
			m_needSendResult = false;

			if (!m_buffer.AnyRetrievable())
				break;
		}

		unsigned long timeOut = maxTime ? SaturatingSubtract(maxTime, timer.ElapsedTime()) : 0;
		if (sender.MustWaitToSend() && !sender.Wait(timeOut, CallStack("NetworkSink::DoFlush() - wait send", 0)))
			break;

		size_t contiguousSize = 0;
		const byte *block = m_buffer.Spy(contiguousSize);

#if CRYPTOPP_TRACE_NETWORK
		OutputDebugString((IntToString((unsigned int)this) + ": Sending " + IntToString(contiguousSize) + " bytes\n").c_str());
#endif
		sender.Send(block, contiguousSize);
		m_needSendResult = true;

		if (maxTime > 0 && timeOut == 0)
			break;
	}

	m_byteCountSinceLastTimerReset += totalFlushSize;
	ComputeCurrentSpeed();

	if (m_buffer.IsEmpty() && !m_needSendResult)
	{
		if (m_eofState == EOF_PENDING_SEND)
		{
			sender.SendEof();
			m_eofState = sender.MustWaitForEof() ? EOF_PENDING_DELIVERY : EOF_DONE;
		}

		while (m_eofState == EOF_PENDING_DELIVERY)
		{
			unsigned long timeOut = maxTime ? SaturatingSubtract(maxTime, timer.ElapsedTime()) : 0;
			if (!sender.Wait(timeOut, CallStack("NetworkSink::DoFlush() - wait EOF", 0)))
				break;

			if (sender.EofSent())
				m_eofState = EOF_DONE;
		}
	}

	return totalFlushSize;
}
