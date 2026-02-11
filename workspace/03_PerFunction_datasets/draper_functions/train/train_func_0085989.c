release(void* ptr)
{
	FastMutex::ScopedLock lock(_mutex);

	_blocks.push_back(reinterpret_cast<char*>(ptr));
}
