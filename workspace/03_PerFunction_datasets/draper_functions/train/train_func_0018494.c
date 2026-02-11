line_get_data(struct tt_line *ln, struct tt_column *cl,
				char *buf, size_t bufsz)
{
	const char *data = ln->data[cl->seqnum];
	const struct tt_symbols *sym;
	char *p = buf;

	memset(buf, 0, bufsz);

	if (!data)
		return NULL;
	if (!(cl->flags & TT_FL_TREE)) {
		strncpy(buf, data, bufsz);
		buf[bufsz - 1] = '\0';
		return buf;
	}
	if (ln->parent) {
		p = line_get_ascii_art(ln->parent, buf, &bufsz);
		if (!p)
			return NULL;
	}

	sym = ln->table->symbols;

	if (!ln->parent)
		snprintf(p, bufsz, "%s", data);
	else if (list_last_entry(&ln->ln_children, &ln->parent->ln_branch))
		snprintf(p, bufsz, "%s%s", sym->right, data);
	else
		snprintf(p, bufsz, "%s%s", sym->branch, data);

	return buf;
}
