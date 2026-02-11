url_check_word (const char *word)
{
	struct {
		gboolean (*match) (const char *word, int *start, int *end);
		int type;
	} m[] = {
	   { match_url,     WORD_URL },
	   { match_email,   WORD_EMAIL },
	   { match_nick,    WORD_NICK },
	   { match_channel, WORD_CHANNEL },
	   { match_host6,   WORD_HOST6 },
	   { match_host,    WORD_HOST },
	   { match_path,    WORD_PATH },
	   { NULL,          0}
	};
	int i;

	laststart = lastend = lasttype = 0;

	for (i = 0; m[i].match; i++)
		if (m[i].match (word, &laststart, &lastend))
		{
			lasttype = m[i].type;
			return lasttype;
		}

	return 0;
}
