waitDequeueNotification(long milliseconds)
{
	while (milliseconds >= 0)
	{
		_mutex.lock();
		NfQueue::iterator it = _nfQueue.begin();
		if (it != _nfQueue.end())
		{
			_mutex.unlock();
			Poco::Timestamp now;
			Timestamp::TimeDiff sleep = it->first - now;
			if (sleep <= 0)
			{
				return dequeueOne(it).duplicate();
			}
			else if (sleep <= 1000*Timestamp::TimeDiff(milliseconds))
			{
				if (!wait(sleep))
				{
					return dequeueOne(it).duplicate();
				}
				else
				{
					milliseconds -= static_cast<long>((now.elapsed() + 999)/1000);
					continue;
				}
			}
		}
		else
		{
			_mutex.unlock();
		}
		if (milliseconds > 0)
		{
			Poco::Timestamp now;
			_nfAvailable.tryWait(milliseconds);
			milliseconds -= static_cast<long>((now.elapsed() + 999)/1000);
		}
		else return 0;
	}
	return 0;
}
