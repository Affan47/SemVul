el_editmode(EditLine *el, int argc, const Char **argv)
{
	const Char *how;

	if (argv == NULL || argc != 2 || argv[1] == NULL)
		return -1;

	how = argv[1];
	if (Strcmp(how, STR("on")) == 0) {
		el->el_flags &= ~EDIT_DISABLED;
		tty_rawmode(el);
	} else if (Strcmp(how, STR("off")) == 0) {
		tty_cookedmode(el);
		el->el_flags |= EDIT_DISABLED;
	}
	else {
		(void) fprintf(el->el_errfile, "edit: Bad value `" FSTR "'.\n",
		    how);
		return -1;
	}
	return 0;
}
