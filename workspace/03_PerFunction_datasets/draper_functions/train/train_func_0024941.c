cli_parse_line(char *line, char *words[], int max_words)
{
	int nwords = 0;
	char *p = line;
	char *word_start = line;
	int inquote = 0;

	while (nwords < max_words - 1)
	{
		if (!*p || *p == inquote || (word_start && !inquote && (isspace(*p) || *p == '|')))
		{
			if (word_start)
			{
				int len = p - word_start;

				memcpy(words[nwords] = malloc(len + 1), word_start, len);
				words[nwords++][len] = 0;
			}

			if (!*p)
				break;

			if (inquote)
				p++;

			inquote = 0;
			word_start = 0;
		}
		else if (*p == '"' || *p == '\'')
		{
		    	inquote = *p++;
			word_start = p;
		}
		else
		{
			if (!word_start)
			{
				if (*p == '|')
				{
				    	words[nwords++] = strdup("|");
				}
				else if (!isspace(*p))
					word_start = p;
			}

			p++;
		}
	}

	return nwords;
}
