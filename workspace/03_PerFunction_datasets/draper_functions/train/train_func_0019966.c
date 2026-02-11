ng_find_reader_magic(char *filename)
{
    struct list_head *item;
    struct ng_reader *reader;
    char blk[512];
    FILE *fp;
    int m;

    if (NULL == (fp = fopen(filename, "r"))) {
	fprintf(stderr,"open %s: %s\n",filename,strerror(errno));
        return NULL;
    }
    memset(blk,0,sizeof(blk));
    fread(blk,1,sizeof(blk),fp);
    fclose(fp);

    list_for_each(item,&ng_readers) {
	reader = list_entry(item, struct ng_reader, list);
	for (m = 0; m < 8 && reader->mlen[m] > 0; m++) {
	    if (0 == memcmp(blk+reader->moff[m],reader->magic[m],
			    reader->mlen[m]))
		return reader;
	}
    }
    if (ng_debug)
	fprintf(stderr,"%s: no reader found [magic]\n",filename);
    return NULL;
}
