processKeyInFocus(const Curses::Key &key)
{
	if (key == key.DEL)
	{
		parent->delAttachment(filename);
		return true;
	}

	return CursesButton::processKeyInFocus(key);
}
