isDestroyed(mail::callback &callback) const
{
	if (myServer.isDestroyed())
	{
		callback.fail("Server connection closed.");
		return true;
	}

	return false;
}
