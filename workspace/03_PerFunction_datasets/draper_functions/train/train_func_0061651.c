add_e820_entry(struct boot_params *params, struct e820entry *entry)
{
	unsigned int nr_e820_entries;

	nr_e820_entries = params->e820_entries;
	if (nr_e820_entries >= E820MAX)
		return 1;

	memcpy(&params->e820_map[nr_e820_entries], entry,
			sizeof(struct e820entry));
	params->e820_entries++;
	return 0;
}
