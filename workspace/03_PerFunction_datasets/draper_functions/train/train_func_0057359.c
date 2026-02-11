gather_dirstat(struct diff_options *opt, struct dirstat_dir *dir,
		unsigned long changed, const char *base, int baselen)
{
	unsigned long this_dir = 0;
	unsigned int sources = 0;
	const char *line_prefix = "";
	struct strbuf *msg = NULL;

	if (opt->output_prefix) {
		msg = opt->output_prefix(opt, opt->output_prefix_data);
		line_prefix = msg->buf;
	}

	while (dir->nr) {
		struct dirstat_file *f = dir->files;
		int namelen = strlen(f->name);
		unsigned long this;
		char *slash;

		if (namelen < baselen)
			break;
		if (memcmp(f->name, base, baselen))
			break;
		slash = strchr(f->name + baselen, '/');
		if (slash) {
			int newbaselen = slash + 1 - f->name;
			this = gather_dirstat(opt, dir, changed, f->name, newbaselen);
			sources++;
		} else {
			this = f->changed;
			dir->files++;
			dir->nr--;
			sources += 2;
		}
		this_dir += this;
	}


	if (baselen && sources != 1) {
		if (this_dir) {
			int permille = this_dir * 1000 / changed;
			if (permille >= dir->permille) {
				fprintf(opt->file, "%s%4d.%01d%% %.*s\n", line_prefix,
					permille / 10, permille % 10, baselen, base);
				if (!dir->cumulative)
					return 0;
			}
		}
	}
	return this_dir;
}
