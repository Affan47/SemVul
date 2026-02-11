genericMessageRead(std::string uid,
					  size_t messageNumber,
					  bool peek,
					  mail::readMode readType,
					  mail::callback::message &callback)
{
	if (f && fInfo.uid == uid)
	{
		if (fseek(f, 0L, SEEK_END) < 0 || fseek(f, 0L, SEEK_SET) < 0)
		{
			callback.fail(strerror(errno));
			return;
		}

		mail::file rf(fileno(f), "r");

		if (!rf)
		{
			callback.fail(strerror(errno));
			return;
		}

		rf.genericMessageRead(this, 0, readType, callback);

		if (ferror(rf))
		{
			callback.fail(strerror(errno));
			return;
		}
	}

	if (!peek)
		genericMarkRead(0);

	callback.success("Ok.");
}
