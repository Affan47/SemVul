readIndex(string msg)
{
	try {
		callback.success(msg);
		delete this;
	} catch (...) {
		delete this;
		LIBMAIL_THROW(LIBMAIL_THROW_EMPTY);
	}
}
