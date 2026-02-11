setStartInterval(long milliseconds)
{
	poco_assert (milliseconds >= 0);
	FastMutex::ScopedLock lock(_mutex);
	_startInterval = milliseconds;
}
