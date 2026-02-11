dump_extension_table(int verbose)
{
	int i;
	struct extension_table *ext;
	struct command_table_entry *cp;
	char buf[BUFSIZE];
	int longest, others;

	if (!extension_table)
		return;

	if (verbose) {
       		for (ext = extension_table; ext; ext = ext->next) {
                        fprintf(fp, "        filename: %s\n", ext->filename);
                        fprintf(fp, "          handle: %lx\n", (ulong)ext->handle);


			fprintf(fp, "           flags: %lx (", ext->flags);
			others = 0;
			if (ext->flags & REGISTERED)
				fprintf(fp, "%sREGISTERED", others++ ?
					"|" : "");
			fprintf(fp, ")\n");
                        fprintf(fp, "            next: %lx\n", (ulong)ext->next);
                        fprintf(fp, "            prev: %lx\n", (ulong)ext->prev);

                        for (i = 0, cp = ext->command_table; cp->name; cp++, i++) {
                        	fprintf(fp, "command_table[%d]: %lx\n", i, (ulong)cp);
				fprintf(fp, "                  name: %s\n", cp->name);
				fprintf(fp, "                  func: %lx\n", (ulong)cp->func);
				fprintf(fp, "             help_data: %lx\n", (ulong)cp->help_data);
				fprintf(fp, "                 flags: %lx (", cp->flags);
				others = 0;
				if (cp->flags & CLEANUP)
					fprintf(fp, "%sCLEANUP", others++ ? "|" : "");
				if (cp->flags & REFRESH_TASK_TABLE)
					fprintf(fp, "%sREFRESH_TASK_TABLE", others++ ? "|" : "");
				if (cp->flags & HIDDEN_COMMAND)
					fprintf(fp, "%sHIDDEN_COMMAND", others++ ? "|" : "");
				fprintf(fp, ")\n");
			}

			if (ext->next)
				fprintf(fp, "\n");
		}
		return;
	}


	for (longest = 0, ext = extension_table; ext; ext = ext->next) {
		if (strlen(ext->filename) > longest)
			longest = strlen(ext->filename);
	}

	fprintf(fp, "%s  COMMANDS\n",
		mkstring(buf, longest, LJUST, "SHARED OBJECT"));
	longest = MAX(longest, strlen("SHARED OBJECT"));

	for (ext = extension_table; ext; ext = ext->next)
		if (ext->next == NULL)
			break;

	do {
                fprintf(fp, "%s  ",
                        mkstring(buf, longest, LJUST, ext->filename));
                for (cp = ext->command_table; cp->name; cp++)
                        fprintf(fp, "%s ", cp->name);
		fprintf(fp, "\n");
	} while ((ext = ext->prev));
}
