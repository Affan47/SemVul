processKey(const Curses::Key &key)
{
	if (key == key_ABORT)
	{
		keepgoing=false;
		myServer::nextScreen= &hierarchyScreen;
		return true;
	}

	return false;
}
