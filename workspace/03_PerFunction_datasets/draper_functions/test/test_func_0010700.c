_delete_part_record(char *name)
{
	int i;

	last_part_update = time(NULL);
	if (name == NULL) {
		i = list_delete_all(part_list, &list_find_part,
				    "universal_key");
	} else
		i = list_delete_all(part_list, &list_find_part, name);
	if ((name == NULL) || (i != 0))
		return 0;

	error("_delete_part_record: attempt to delete non-existent "
	      "partition %s", name);
	return ENOENT;
}
