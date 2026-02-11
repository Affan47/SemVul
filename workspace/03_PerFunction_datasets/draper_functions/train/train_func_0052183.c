start(Thread::Priority priority, Runnable& target)
{
	FastMutex::ScopedLock lock(_mutex);

	poco_assert (_pTarget == 0);

	_pTarget = &target;
	_thread.setPriority(priority);
	_targetReady.set();
}
