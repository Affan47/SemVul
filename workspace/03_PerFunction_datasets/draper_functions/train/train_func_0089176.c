print_text(void *_object, const char *str, int lstr, bool esc = false)
{
	QString s = QString::fromUtf8(str, lstr);
  int line, col;
  uint i, len;

	WIDGET->getCursor(&line, &col);
	if (col == 0)
	{

		DOC->remove(line, 0, line, DOC->lineLength(line));
		WIDGET->cursorGoto(line, 0, false);
	}


	if (!esc)
	{
		i = 0;
		for (;;)
		{
			if (col == MAX_CONSOLE_WIDTH)
			{
				WIDGET->insert("\n");
				col = 0;
			}
			len = s.length() - i;
			if ((col + len) >= MAX_CONSOLE_WIDTH)
				len = MAX_CONSOLE_WIDTH - col;
			WIDGET->insert(s.mid(i, len));
			i += len;
			if (i >= (uint)s.length())
				break;
			col += len;
		}
	}
	else
	{
		if (col >= MAX_CONSOLE_WIDTH)
			WIDGET->insert("\n");
		WIDGET->insert(s);
	}
}
