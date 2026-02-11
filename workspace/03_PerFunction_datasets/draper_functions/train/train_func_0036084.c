processKeyInFocus(const Key &key)
{
	if ((key.plain() && key.ukey == '\t')
	    || key == key.DOWN || key == key.SHIFTDOWN
	    || key == key.ENTER)
	{
		transferNextFocus();
		return true;
	}

	if (key == key.UP || key == key.SHIFTUP)
	{
		transferPrevFocus();
		return true;
	}

	if (key == key.PGUP || key == key.SHIFTPGUP)
	{
		int h=getScreenHeight();

		if (h > 5)
			h -= 5;

		if (h < 5)
			h=5;

		while (h)
		{
			processKey(Key(key ==
				       Key::PGUP ? Key::UP:Key::SHIFTUP));
			--h;
		}
		return true;
	}

	if (key == key.PGDN || key == key.SHIFTPGDN)
	{
		int h=getScreenHeight();

		if (h > 5)
			h -= 5;

		if (h < 5)
			h=5;

		while (h)
		{
			processKey(Key(key ==
				       Key::PGDN ? Key::DOWN:Key::SHIFTDOWN));
			--h;
		}
		return true;
	}

	return false;
}
