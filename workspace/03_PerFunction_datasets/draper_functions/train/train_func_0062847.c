testArchive()
{
	std::string name = filename();
	try
	{
		AutoPtr<FileChannel> pChannel = new FileChannel(name);
		pChannel->setProperty(FileChannel::PROP_ROTATION, "2 K");
		pChannel->setProperty(FileChannel::PROP_ARCHIVE, "number");
		pChannel->open();
		Message msg("source", "This is a log file entry", Message::PRIO_INFORMATION);
		for (int i = 0; i < 200; ++i)
		{
			pChannel->log(msg);
		}
		File f(name + ".0");
		assert (f.exists());
	}
	catch (...)
	{
		remove(name);
		throw;
	}
	remove(name);
}
