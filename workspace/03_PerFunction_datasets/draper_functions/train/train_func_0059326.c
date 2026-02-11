add_param(int t, char *name, void *addr)
{
	entry *e;
	if (top == NULL) {
		bottom = top = e = (entry *) malloc(sizeof(entry));
	} else {
		e = (entry *) malloc(sizeof(entry));
		top->next = e;
		top = e;
	}
	if (e == NULL) {printf("parameter manager out of memory!\n"); exit(1);}
	top->t = t;
	top->name = name;
	top->addr = addr;
	top->next = NULL;
	search_command_line(name);
}
