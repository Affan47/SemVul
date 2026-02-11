cgit_print_snapshot(const char *head, const char *hex,
			 const char *filename, int snapshots, int dwim)
{
	const struct cgit_snapshot_format* f;
	char *prefix = NULL;

	if (!filename) {
		show_error("No snapshot name specified");
		return;
	}

	f = get_format(filename);
	if (!f) {
		show_error(xstrdup(fmt("Unsupported snapshot format: %s",
				       filename)));
		return;
	}

	if (!hex && dwim) {
		hex = get_ref_from_filename(ctx.repo->url, filename, f);
		if (hex == NULL) {
			html_status(404, "Not found", 0);
			return;
		}
		prefix = xstrdup(filename);
		prefix[strlen(filename) - strlen(f->suffix)] = '\0';
	}

	if (!hex)
		hex = head;

	if (!prefix)
		prefix = xstrdup(cgit_repobasename(ctx.repo->url));

	make_snapshot(f, hex, prefix, filename);
	free(prefix);
}
