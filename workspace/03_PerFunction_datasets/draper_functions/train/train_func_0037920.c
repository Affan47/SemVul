remove_local()
{
	int i;
	CLASS_SYMBOL *sym;

	for (i = 0; i < ARRAY_count(func->local); i++)
	{
		sym = CLASS_get_symbol(JOB->class, func->local[i].index);
		TYPE_clear(&sym->local.type);
	}
}
