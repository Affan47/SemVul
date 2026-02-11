store_sysmap_symbols(void)
{
	int c, first;
	long symcount;
	char buf[BUFSIZE];
	char name[BUFSIZE];
	FILE *map;
        char *mapitems[MAXARGS];
	struct syment *sp, syment;

	if ((map = fopen(pc->system_map, "r")) == NULL)
		error(FATAL, "cannot open %s\n", pc->system_map);

	symcount = 0;
	while (fgets(buf, BUFSIZE, map))
		symcount++;

        if ((st->symtable = (struct syment *)
             calloc(symcount, sizeof(struct syment))) == NULL)
                error(FATAL, "symbol table syment space malloc: %s\n",
                        strerror(errno));

        if (!namespace_ctl(NAMESPACE_INIT, &st->kernel_namespace,
            (void *)symcount, NULL))
                error(FATAL, "symbol table namespace malloc: %s\n",
                        strerror(errno));

	if (!machine_type("X86"))
		kt->flags &= ~RELOC_SET;

	first = 0;
        st->syment_size = symcount * sizeof(struct syment);
        st->symcnt = 0;
        sp = st->symtable;

	rewind(map);

	while (fgets(buf, BUFSIZE, map)) {
		if ((c = parse_line(buf, mapitems)) != 3)
			continue;

		syment.value = htol(mapitems[0], FAULT_ON_ERROR, NULL);
		syment.type = mapitems[1][0];
		syment.name = mapitems[2];

		strcpy(name, syment.name);
		strip_symbol_end(name, NULL);

                if (machdep->verify_symbol(name, syment.value,
		    syment.type)) {
			if (kt->flags & RELOC_SET)
				sp->value = relocate(syment.value,
					syment.name, !(first++));
			else
				sp->value = syment.value;
                        sp->type = syment.type;
                        namespace_ctl(NAMESPACE_INSTALL, &st->kernel_namespace,
                                sp, name);
                        sp++;
                        st->symcnt++;
                }
	}

	fclose(map);

        st->symend = &st->symtable[st->symcnt];

        st->flags |= KERNEL_SYMS;

        namespace_ctl(NAMESPACE_COMPLETE, &st->kernel_namespace,
                st->symtable, st->symend);

	symname_hash_init();
	symval_hash_init();
}
