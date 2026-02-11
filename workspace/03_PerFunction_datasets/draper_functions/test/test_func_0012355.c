tree_grep(struct view *view, struct line *line)
{
	struct tree_entry *entry = line->data;
	const char *text[] = {
		entry->name,
		opt_author ? entry->author : "",
		mkdate(&entry->time, opt_date),
		NULL
	};

	return grep_text(view, text);
}
