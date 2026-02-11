text_split_by_space(char *text, char *texts[], int size)
{
	int index;

	if (size == 0)
	{
		return 0;
	}

	index = 0;
	texts[0] = text;

	while (1)
	{
		switch (*text)
		{
		case 0:
			return texts[index] < text ? index + 1 : index;

		case ' ':
		case '\t':
		case '\f':
		case '\r':
		case '\n':
			if (texts[index] < text)
			{
				*text = 0;
				index++;

				if (index < size)
				{
					texts[index] = text + 1;
				}
				else
				{
					return index + 1;
				}
			}
			else
			{
				texts[index] = text + 1;
			}

			break;
		}

		text++;
	}

	return 0;
}
