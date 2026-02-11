create_new_newsrc(char *path)
{
    FILE	*fp;
    int		c;

    fp = fopen_mkdir(path, "w", True);
    popup_title_notice(fp ? "Created newsrc file" :
		       "Failed to create newsrc file", path, fp == NULL);
    if (!fp)
	return;

    if (global.auto_subscribe)
	if (global.auto_subscribe[0] != '/')
	    fputs(global.auto_subscribe, fp);
	else {
	    FILE	*ng = fopen(global.auto_subscribe, "r");

	    if (!ng)
		perror(global.auto_subscribe);
	    else {
		while ((c = getc(ng)) != EOF)
		    putc(c, fp);
		fclose(ng);
	    }
	}

    fclose(fp);
}
