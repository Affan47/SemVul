icon_files(void)
{
    char **list, *ret;
    char buf[GNAME_MAX], path[GPATH_MAX], path_i[GPATH_MAX];
    int i, count;
    size_t len;
    DIR *dir, *dir_i;
    struct dirent *d, *d_i;

    list = NULL;
    len = 0;
    sprintf(path, "%s/etc/symbol", G_gisbase());

    dir = opendir(path);
    if (!dir)
	return NULL;

    count = 0;


    while ((d = readdir(dir))) {
	if (d->d_name[0] == '.')
	    continue;

	sprintf(path_i, "%s/etc/symbol/%s", G_gisbase(), d->d_name);
	dir_i = opendir(path_i);

	if (!dir_i)
	    continue;


	while ((d_i = readdir(dir_i))) {
	    if (d_i->d_name[0] == '.')
		continue;

	    list = G_realloc(list, (count + 1) * sizeof(char *));

	    sprintf(buf, "%s/%s", d->d_name, d_i->d_name);
	    list[count++] = G_store(buf);

	    len += strlen(d->d_name) + strlen(d_i->d_name) + 2;
	}

	closedir(dir_i);
    }

    closedir(dir);

    qsort(list, count, sizeof(char *), cmp);

    if (len > 0) {
	ret = G_malloc((len + 1) * sizeof(char));
	*ret = '\0';
	for (i = 0; i < count; i++) {
	    if (i > 0)
		strcat(ret, ",");
	    strcat(ret, list[i]);
	    G_free(list[i]);
	}
	G_free(list);
    }
    else {
	ret = G_store("");
    }

    return ret;
}
