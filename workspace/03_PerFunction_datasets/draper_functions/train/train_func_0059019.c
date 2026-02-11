gar_select_basemaps(struct gimg *g)
{
	struct gar_subfile *sub;
	int havebase = 0;
	int id;
	unsigned int minid = ~0;
	char *ptr, *eptr;

	log(11, "Selecting basemap ...\n");
	list_for_entry(sub, &g->lsubfiles, l) {
		if (*sub->mapid == 'I') {
			ptr = sub->mapid+1;
			id = strtol(ptr, &eptr, 16);
			if (!(*ptr && *eptr == '\0')) {
				havebase = gar_check_basemap(sub);
			}
			continue;
		}
		if (*sub->mapid >= 'A' && *sub->mapid <= 'Z') {
			havebase = gar_check_basemap(sub);
		}
	}
	if (havebase)
		return 1;

	list_for_entry(sub, &g->lsubfiles, l) {
		if (*sub->mapid < '0' || *sub->mapid > '9') {
			havebase = gar_check_basemap(sub);
		}
	}

	if (havebase)
		return 1;
	list_for_entry(sub, &g->lsubfiles, l) {
		id = atoi(sub->mapid);
		if (id < minid)
			minid = id;
	}
	list_for_entry(sub, &g->lsubfiles, l) {
		id = atoi(sub->mapid);
		if (id == minid) {
			havebase = gar_check_basemap(sub);
			if (havebase)
				break;
		}
	}
#if 0
	if (!havebase) {
		log(1, "Warning no basemap found guessing\n");
		list_for_entry(sub, &g->lsubfiles, l) {
			minid = atoi(sub->mapid);
			havebase = gar_check_basemap(sub);
			if (havebase)
				break;
		}
	}
#endif
	return minid;
}
