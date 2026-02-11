getNextLine(char * buff, int len, BuildType type)
{
	if (type == File)
	{
		if (mFile != NULL)
			return fgets(buff, len, mFile);

		const char * from = configTemplate[++templateCounter];
		if (strcmp("EOF",from) == 0)
			return NULL;

		strncpy(buff,from, len);
		return buff;
	}
	else
	{
		if (mEditorIterator != mEditor->document()->end())
		{
			len = mEditorIterator.length();
			if (len > 0)
			{
				strncpy(buff,mEditorIterator.text().toAscii().data(),len-1);
				buff[len-1] = '\0';
			}
			else
				buff[0] = '\0';
			mEditorIterator = mEditorIterator.next();
			return buff;
		}
		else
			return NULL;

	}
}
