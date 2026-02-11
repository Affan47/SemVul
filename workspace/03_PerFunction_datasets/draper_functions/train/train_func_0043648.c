add_mapping(struct string_list *map,
			char *new_name, char *new_email, char *old_name, char *old_email)
{
	struct mailmap_entry *me;
	int index;
	char *p;

	if (old_email)
		for (p = old_email; *p; p++)
			*p = tolower(*p);
	if (new_email)
		for (p = new_email; *p; p++)
			*p = tolower(*p);

	if (old_email == NULL) {
		old_email = new_email;
		new_email = NULL;
	}

	if ((index = string_list_find_insert_index(map, old_email, 1)) < 0) {

		index = -1 - index;
	} else {

		struct string_list_item *item = string_list_insert_at_index(map, index, old_email);
		item->util = xmalloc(sizeof(struct mailmap_entry));
		memset(item->util, 0, sizeof(struct mailmap_entry));
		((struct mailmap_entry *)item->util)->namemap.strdup_strings = 1;
	}
	me = (struct mailmap_entry *)map->items[index].util;

	if (old_name == NULL) {
		debug_mm("mailmap: adding (simple) entry for %s at index %d\n", old_email, index);

		if (new_name) {
			free(me->name);
			me->name = xstrdup(new_name);
		}
		if (new_email) {
			free(me->email);
			me->email = xstrdup(new_email);
		}
	} else {
		struct mailmap_info *mi = xmalloc(sizeof(struct mailmap_info));
		debug_mm("mailmap: adding (complex) entry for %s at index %d\n", old_email, index);
		if (new_name)
			mi->name = xstrdup(new_name);
		if (new_email)
			mi->email = xstrdup(new_email);
		string_list_insert(&me->namemap, old_name)->util = mi;
	}

	debug_mm("mailmap:  '%s' <%s> -> '%s' <%s>\n",
		 old_name, old_email, new_name, new_email);
}
