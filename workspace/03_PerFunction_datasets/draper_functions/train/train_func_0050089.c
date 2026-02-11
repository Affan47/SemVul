desktop_read_entry(char *filename, char *entry, char *dest, size_t max)
{
    struct list_head file;
    char *value;
    int rc = 0;

    read_file(filename,&file);
    if (debug)
	dump_file(&file);
    value = get_entry(&file,entry);
    if (NULL != value) {
	rc = utf8_to_locale(value,dest,max);
	if (rc && debug)
	    fprintf(stderr,"# %s\n",dest);
    };
    free_file(&file);
    return rc;
}
