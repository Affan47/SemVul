checkServer()
{
	if (isDestroyed())
	{
		fail("Server connection closed.");
		return false;
	}

	return true;
}
