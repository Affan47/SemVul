main_grep(struct view *view, struct line *line)
{
	struct commit *commit = line->data;
	enum { S_TITLE, S_AUTHOR, S_DATE, S_REFS, S_END } state;
	char buf[DATE_COLS + 1];
	regmatch_t pmatch;

	for (state = S_TITLE; state < S_END; state++) {
		char *text;

		switch (state) {
		case S_TITLE:	text = commit->title;	break;
		case S_AUTHOR:
			if (!opt_author)
				continue;
			text = commit->author;
			break;
		case S_DATE:
			if (!opt_date)
				continue;
			if (!strftime(buf, sizeof(buf), DATE_FORMAT, &commit->time))
				continue;
			text = buf;
			break;
		case S_REFS:
			if (!opt_show_refs)
				continue;
			if (grep_refs(commit->refs, view->regex) == TRUE)
				return TRUE;
			continue;
		default:
			return FALSE;
		}

		if (regexec(view->regex, text, 1, &pmatch, 0) != REG_NOMATCH)
			return TRUE;
	}

	return FALSE;
}
