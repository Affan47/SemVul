do_helpcard(BASE *base, unsigned char *s, void *object, int *notify)
{
	struct help *new_help;

	if (notify)
		*notify = 1;
	if (!s || !*s) {
		while (help_actual->prev != NULL)

			help_actual = help_actual->prev;
		help_off(base->parent->t);
		return (0);
	}
	if ((new_help = find_context_help(s)) != NULL) {
		help_actual = new_help;
		return (help_on(base->parent->t));
	}
	return (-1);
}
