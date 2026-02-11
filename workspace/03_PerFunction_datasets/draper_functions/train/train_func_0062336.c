open()
{
	FastMutex::ScopedLock lock(_threadMutex);

	if (!_thread.isRunning())
		_thread.start(*this);
}
