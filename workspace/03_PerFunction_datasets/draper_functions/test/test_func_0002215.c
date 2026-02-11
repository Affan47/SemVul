c_find_ident(struct c_ident *list,
	struct c_ident *globals, char *name)
{
	struct c_ident *current;

	if ((current = list) != globals)
	do {
		if (!strcmp(name, current->name)) break;
	} while ((current = current->next) != globals);

	if (current != globals)
		return current;
	else
		return NULL;
}
