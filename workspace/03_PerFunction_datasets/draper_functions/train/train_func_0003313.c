add_pager_refs(struct view *view, struct line *line)
{
	char buf[SIZEOF_STR];
	char *commit_id = (char *)line->data + STRING_SIZE("commit ");
	struct ref **refs;
	size_t bufpos = 0, refpos = 0;
	const char *sep = "Refs: ";
	bool is_tag = FALSE;

	assert(line->type == LINE_COMMIT);

	refs = get_refs(commit_id);
	if (!refs) {
		if (view == VIEW(REQ_VIEW_DIFF))
			goto try_add_describe_ref;
		return;
	}

	do {
		struct ref *ref = refs[refpos];
		char *fmt = ref->tag    ? "%s[%s]" :
		            ref->remote ? "%s<%s>" : "%s%s";

		if (!string_format_from(buf, &bufpos, fmt, sep, ref->name))
			return;
		sep = ", ";
		if (ref->tag)
			is_tag = TRUE;
	} while (refs[refpos++]->next);

	if (!is_tag && view == VIEW(REQ_VIEW_DIFF)) {
try_add_describe_ref:

		if (!add_describe_ref(buf, &bufpos, commit_id, sep))
			return;
	}

	if (bufpos == 0)
		return;

	if (!realloc_lines(view, view->line_size + 1))
		return;

	add_line_text(view, buf, LINE_PP_REFS);
}
