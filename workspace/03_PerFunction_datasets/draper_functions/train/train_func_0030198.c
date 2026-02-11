mc_maclist_read_from_file (const char *fullpath)
{
	FILE *f;
	char *line;
	char  tmp[512];
	int   num =0;
	card_mac_list_item_t *list;

	if ((f = fopen(fullpath, "r")) == NULL) {
		fprintf (stderr, "ERROR: Can't read MAC list file \"%s\", It looks like a bad installation\n", fullpath);
		return NULL;
	}


	while ((line = fgets (tmp, 511, f)) != NULL) num++;
	rewind (f);


	list = (card_mac_list_item_t *) malloc (sizeof(card_mac_list_item_t) * (num+1));


	num = 0;
	while ((line = fgets (tmp, 511, f)) != NULL) {
		list[num].byte[0] = (char) (strtoul (line, NULL, 16) & 0xFF);
		list[num].byte[1] = (char) (strtoul (line+3, NULL, 16) & 0xFF);
		list[num].byte[2] = (char) (strtoul (line+6, NULL, 16) & 0xFF);

		line[strlen(line)-1] = '\0';
		list[num].name = (char*)(strdup(line+9));

		num ++;
	}


	list[num].byte[0] = list[num].byte[1] = list[num].byte[2] = 0;
	list[num].name = NULL;

	fclose (f);

	return list;
}
