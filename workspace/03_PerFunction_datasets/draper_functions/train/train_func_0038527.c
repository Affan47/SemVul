show_mode_change(struct diff_filepair *p, int show_name)
{
	if (p->one->mode && p->two->mode && p->one->mode != p->two->mode) {
		if (show_name) {
			char *name = quote_one(p->two->path);
			printf(" mode change %06o => %06o %s\n",
			       p->one->mode, p->two->mode, name);
			free(name);
		}
		else
			printf(" mode change %06o => %06o\n",
			       p->one->mode, p->two->mode);
	}
}
