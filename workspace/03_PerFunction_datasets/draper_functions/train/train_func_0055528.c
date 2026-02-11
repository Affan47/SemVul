program_list_reverse (struct cb_program *p)
{
	struct cb_program	*next;
	struct cb_program	*last = NULL;

	for (; p; p = next) {
		next = p->next_program;
		p->next_program = last;
		last = p;
	}
	return last;
}
