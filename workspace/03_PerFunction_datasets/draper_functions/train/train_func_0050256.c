ok(std::string msg)
{
	if (go())
	{
		doDestroy=false;
		return true;
	}

	return smapHandler::ok(msg);
}
