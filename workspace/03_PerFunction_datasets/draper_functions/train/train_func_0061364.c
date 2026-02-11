add_dump(
    char *      hostname,
    char *	date,
    int		level,
    char *	tape,
    off_t	file,
    int		partnum,
    int		maxpart)
{
    DUMP_ITEM *new, *item, *before;
    int isafile = 0;

    if(tape[0] == '/')
	isafile = 1;


    if (partnum > 1) {
	for(item = disk_hist, before = NULL; item;
	    before = item, item = item->next) {
	    if (!strcmp(item->date, date) &&
		    item->level == level && item->is_split) {
		item->tapes = append_to_tapelist(item->tapes, tape, file,
						 partnum, isafile);
		if (maxpart > item->maxpart)
		    item->maxpart = maxpart;
		return;
	    }
	}
	return;
    }

    new = (DUMP_ITEM *)alloc(SIZEOF(DUMP_ITEM));
    strncpy(new->date, date, SIZEOF(new->date)-1);
    new->date[SIZEOF(new->date)-1] = '\0';
    new->level = level;
    strncpy(new->tape, tape, SIZEOF(new->tape)-1);
    new->tape[SIZEOF(new->tape)-1] = '\0';
    new->file = file;
    new->maxpart = maxpart;
    if(partnum == -1)
        new->is_split = 0;
    else
        new->is_split = 1;
    new->tapes = NULL;
    new->hostname = stralloc(hostname);

    new->tapes = append_to_tapelist(new->tapes, tape, file, partnum, isafile);

    if (disk_hist == NULL)
    {
	disk_hist = new;
	new->next = NULL;
	return;
    }


    if (strcmp(disk_hist->date, new->date) <= 0)
    {
	new->next = disk_hist;
	disk_hist = new;
	return;
    }


    before = disk_hist;
    item = disk_hist->next;
    while ((item != NULL) && (strcmp(item->date, new->date) > 0))
    {
	before = item;
	item = item->next;
    }
    new->next = item;
    before->next = new;
}
