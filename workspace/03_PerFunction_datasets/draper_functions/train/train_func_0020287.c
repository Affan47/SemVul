pnm_init(FILE *fp, char *filename, unsigned int page,
	 struct ida_image_info *i, int thumbnail)
{
    struct ppm_state *h;
    char line[1024];
    char p;

    h = malloc(sizeof(*h));
    memset(h,0,sizeof(*h));

    h->infile = fp;
    fgets(line,sizeof(line),fp);
    p = line[1];
    fgets(line,sizeof(line),fp);
    while ('#' == line[0])
	fgets(line,sizeof(line),fp);
    sscanf(line,"%d %d",&h->width,&h->height);
    if (p != '4')
	fgets(line,sizeof(line),fp);
    if (0 == h->width || 0 == h->height)
	goto oops;
    i->width  = h->width;
    i->height = h->height;
    i->npages = 1;
    h->row = malloc(h->width*3);

    return h;

 oops:
    fclose(fp);
    free(h);
    return NULL;
}
