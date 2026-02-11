tag_push (const char *name)
{
	if (!tag_list) {
		tag_size = 128;
		tag_list = malloc (sizeof (char *) * tag_size);
		if (!tag_list) exit (2);
	}
	tag_list[tag_pos] = hash_insert (tag_table, name);
	if (!tag_list[tag_pos]) exit (2);
	tag_pos++;
	if (tag_pos == tag_size) {
		char **tmp;
		tmp = malloc (sizeof (char *) * tag_size * 2);
		if (!tmp) exit (2);
		memcpy (tmp, tag_list, sizeof (char *) * tag_size);
		free (tag_list);
		tag_list = tmp;
		tag_size *= 2;
	}
}
