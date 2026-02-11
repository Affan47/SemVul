scan(DIR *dp, int check_ptr)
{
    static off_t prev_pos;
    struct dirent *ent;
    int found = 0;
    int retval = 0;

    if (check_ptr) {
	if (prev_pos != telldir(dp)) return -1;
	CRUT_DEBUG("Verified position %d", (int)prev_pos);
    }

    rewinddir(dp);

    while (!found && ((ent = readdir(dp)) != NULL)) {
	CRUT_DEBUG("Entry '%s'", ent->d_name);
	if (!strcmp(ent->d_name, MYNAME)) {
	    CRUT_DEBUG("Found '" MYNAME "'");
	    found = 1;
       	}
    }

    if (!found) {
	retval = -1;
    } else if (!check_ptr) {
	prev_pos = telldir(dp);
	if ((int)prev_pos == -1) retval = -1;
	CRUT_DEBUG("Saved position %d", (int)prev_pos);
    }

    return retval;
}
