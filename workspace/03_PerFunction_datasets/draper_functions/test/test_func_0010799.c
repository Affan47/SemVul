open_null_read(int fd)
{
    struct fileinfo *fcb = &G__.fileinfo[fd];
    char *name, *mapset, *dummy;
    int null_fd;

    if (fcb->null_file_exists == 0)
	return -1;

    if (fcb->reclass_flag) {
	name = fcb->reclass.name;
	mapset = fcb->reclass.mapset;
    }
    else {
	name = fcb->name;
	mapset = fcb->mapset;
    }

    dummy = G_find_file_misc("cell_misc", NULL_FILE, name, mapset);

    if (!dummy) {

	fcb->null_file_exists = 0;
	return -1;
    }

    null_fd = G_open_old_misc("cell_misc", NULL_FILE, name, mapset);
    if (null_fd < 0)
	return -1;

    fcb->null_file_exists = 1;

    return null_fd;
}
