new_partition(void) {
	int i, free_primary = 0;

	if (warn_geometry())
		return;

	if (disklabel == SUN_LABEL) {
		add_sun_partition(get_partition(0, partitions), LINUX_NATIVE);
		return;
	}

	if (disklabel == SGI_LABEL) {
		sgi_add_partition(get_partition(0, partitions), LINUX_NATIVE);
		return;
	}

	if (disklabel == AIX_LABEL) {
		printf(_("\tSorry - this fdisk cannot handle AIX disk labels."
			 "\n\tIf you want to add DOS-type partitions, create"
			 "\n\ta new empty DOS partition table first. (Use o.)"
			 "\n\tWARNING: "
			 "This will destroy the present disk contents.\n"));
		return;
	}

	if (disklabel == MAC_LABEL) {
		printf(_("\tSorry - this fdisk cannot handle Mac disk labels."
		         "\n\tIf you want to add DOS-type partitions, create"
		         "\n\ta new empty DOS partition table first. (Use o.)"
		         "\n\tWARNING: "
		         "This will destroy the present disk contents.\n"));
		 return;
	}

	for (i = 0; i < 4; i++)
		free_primary += !ptes[i].part_table->sys_ind;

	if (!free_primary && partitions >= MAXIMUM_PARTS) {
		printf(_("The maximum number of partitions has been created\n"));
		return;
	}

	if (!free_primary) {
		if (extended_offset) {
			printf(_("All primary partitions are in use\n"));
			add_logical();
		} else
			printf(_("If you want to create more than four partitions, you must replace a\n"
				 "primary partition with an extended partition first.\n"));
	} else if (partitions >= MAXIMUM_PARTS) {
		printf(_("All logical partitions are in use\n"));
		printf(_("Adding a primary partition\n"));
		add_partition(get_partition(0, 4), LINUX_NATIVE);
	} else {
		char c, dflt, line[LINE_LENGTH];

		dflt = (free_primary == 1 && !extended_offset) ? 'e' : 'p';
		snprintf(line, sizeof(line),
			 _("Partition type:\n"
			   "   p   primary (%d primary, %d extended, %d free)\n"
			   "%s\n"
			   "Select (default %c): "),
			 4 - (extended_offset ? 1 : 0) - free_primary, extended_offset ? 1 : 0, free_primary,
			 extended_offset ? _("   l   logical (numbered from 5)") : _("   e   extended"),
			 dflt);

		c = tolower(read_chars(line));
		if (c == '\n') {
			c = dflt;
			printf(_("Using default response %c\n"), c);
		}
		if (c == 'p') {
			int i = get_nonexisting_partition(0, 4);
			if (i >= 0)
				add_partition(i, LINUX_NATIVE);
			return;
		} else if (c == 'l' && extended_offset) {
			add_logical();
			return;
		} else if (c == 'e' && !extended_offset) {
			int i = get_nonexisting_partition(0, 4);
			if (i >= 0)
				add_partition(i, EXTENDED);
			return;
		} else
			printf(_("Invalid partition type `%c'\n"), c);
	}
}
