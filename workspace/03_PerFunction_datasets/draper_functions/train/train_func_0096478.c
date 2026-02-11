kvmdump_init(char *filename, FILE *fptr)
{
	int i, page_size;
        struct command_table_entry *cp;
	char *cachebuf;
	FILE *tmpfp;

	if (!machine_type("X86") && !machine_type("X86_64")) {
		error(FATAL,
		    "invalid or unsupported host architecture for KVM: %s\n",
			MACHINE_TYPE);
		return FALSE;
	}

	kvm->ofp = fptr;
	kvm->debug = &pc->debug;
	page_size = memory_page_size();

#ifdef X86_64
	kvm->kvbase = __START_KERNEL_map;
#endif

	switch (kvm->flags & (TMPFILE|MAPFILE|MAPFILE_APPENDED))
	{
	case MAPFILE_APPENDED:
		kvm->mapfd = kvm->vmfd;
		break;

	case MAPFILE|MAPFILE_APPENDED:
	case MAPFILE:
		break;

	default:
		if (kvmdump_mapfile_exists())
			break;

		if ((tmpfp = tmpfile()) == NULL)
			error(FATAL,
			    "cannot create tmpfile for KVM file offsets: %s\n",
				strerror(errno));

		kvm->mapfd = fileno(tmpfp);
		kvm->flags |= TMPFILE;
		break;
	}

        if ((cachebuf = calloc(1, KVMDUMP_CACHED_PAGES * page_size)) == NULL)
                error(FATAL, "%s: cannot malloc KVM page_cache_buf\n");

	for (i = 0; i < KVMDUMP_CACHED_PAGES; i++) {
		kvm->page_cache[i].paddr = CACHE_UNUSED;
		kvm->page_cache[i].bufptr = cachebuf + (i * page_size);
	}

	kvmdump_regs_store(KVMDUMP_REGS_START, NULL);

	if (qemu_init(filename)) {
		switch (kvm->flags & (TMPFILE|MAPFILE|MAPFILE_APPENDED))
		{
		case TMPFILE:
			kvmdump_regs_store(KVMDUMP_REGS_END, NULL);
			write_mapfile_trailer();
			break;

		case MAPFILE:
		case MAPFILE_APPENDED:
		case MAPFILE|MAPFILE_APPENDED:
			read_mapfile_trailer();
			kvmdump_regs_store(KVMDUMP_REGS_END, NULL);
			break;
		}

		for (cp = pc->cmd_table; cp->name; cp++) {
			if (STREQ(cp->name, "map")) {
				cp->flags &= ~HIDDEN_COMMAND;
				break;
			}
		}

		kvm->flags |= KVMDUMP_LOCAL;
		return TRUE;
	} else
		return FALSE;
}
