registerFile(const std::string& path)
	{
		FastMutex::ScopedLock lock(_mutex);

		Path p(path);
		_files.insert(p.absolute().toString());
	}
