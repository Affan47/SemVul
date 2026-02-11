output_class_ref(void)
{
	int i, n;
	SYMBOL *sym;
	CLASS_REF *ref;

	n = ARRAY_count(Class->class);

	begin_section("External classes", sizeof(int));

	for (i = 0; i < n; i++)
	{
		ref = &Class->class[i];
		sym = TABLE_get_symbol(Class->table, ref->index);
		if (ref->used)
		{
			if (ref->exported)
				write_int(-get_string(sym->name, sym->len));
			else
				write_int(get_string(sym->name, sym->len));
		}
		else
		{
			if (JOB->verbose)
				printf("Ignoring class %.*s\n", sym->len, sym->name);
			write_int(-1);
		}
	}

	end_section();
}
