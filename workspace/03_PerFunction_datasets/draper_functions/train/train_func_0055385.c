write_file(char *filename, struct list_head *file)
{
    struct desktop_line *l;
    struct list_head *item;
    FILE *fp;

    fp = fopen(filename,"w");
    if (NULL == fp) {
	fprintf(stderr,"open %s: %s\n",filename,strerror(errno));
	return 0;
    }
    list_for_each(item,file) {
	l = list_entry(item, struct desktop_line, next);
	fprintf(fp,"%s\n",l->line);
    }
    fclose(fp);
    return 0;
}
