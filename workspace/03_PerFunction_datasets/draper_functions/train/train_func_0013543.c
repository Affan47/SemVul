getattrsfile(const char *filename, PAIR_LIST **pair_list)
{
	int rcode;
	PAIR_LIST *attrs = NULL;
	PAIR_LIST *entry;
	VALUE_PAIR *vp;

	rcode = pairlist_read(filename, &attrs, 1);
	if (rcode < 0) {
		return -1;
	}


	entry = attrs;
	while (entry) {

		entry->check = entry->reply;
		entry->reply = NULL;

		for (vp = entry->check; vp != NULL; vp = vp->next) {


		    if (!(vp->attribute & ~0xffff) &&
			 (vp->attribute > 0xff) &&
			 (vp->attribute > 1000)) {
			log_debug("[%s]:%d WARNING! Check item \"%s\"\n"
				  "\tfound in filter list for realm \"%s\".\n",
				  filename, entry->lineno, vp->name,
				  entry->name);
		    }
		}

		entry = entry->next;
	}

	*pair_list = attrs;
	return 0;
}
