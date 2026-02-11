disconnected()
{
	if (ptr == NULL)
	{
		if (errmsg.size() == 0)
			errmsg="Lost server connection.";
		return true;
	}
	return false;
}
