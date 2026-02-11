icq_get_groups(int idx, int dat, struct groups group_array[],
	struct my_details *my_details)
{
	struct idxEntry entry = { 0, 0, 0, 0, 0 };
	guint32 length = 0;
	guint16 i, group_length;

	if (!find_idx_entry(idx, &entry, MY_DETAILS, FIRST_IDX)) {
		eb_debug(DBG_MOD, "Can't find my details\n");
		return 0;
	}
	lseek(dat, entry.dat_offset, SEEK_SET);
	lseek(dat, 12, SEEK_CUR);
	read(dat, &length, 1);
	if (length != 0xe4)
		return 0;

	lseek(dat, 29, SEEK_CUR);
	parse_my_details(dat, my_details);
	pass_strings(dat, 1, 0, 18);
	pass_strings(dat, 3, 0, 21);
	read(dat, &length, 4);
	for (i = 0; length > 0; length--) {
		read(dat, &group_array[i].number, 4);
		read(dat, &group_length, 2);
		read(dat, group_array[i].name, group_length);
		lseek(dat, 6, SEEK_CUR);
		i++;
	}
	group_array[i].number = IGNORE_FOLDER;
	memcpy(group_array[i++].name, "Ignore\0", sizeof("Ignore\0"));
	group_array[i].number = LAST_FOLDER;
	group_array[i++].name[0] = 0;
	return 1;
}
