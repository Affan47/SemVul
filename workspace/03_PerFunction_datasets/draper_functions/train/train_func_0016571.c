babel_init_raw_ctx(void *sf, int32 extent, void *bhp)
{
 struct babel_handler *bh=(struct babel_handler *) bhp;
 char *b;
 bh->treaty_handler=NULL;
 bh->treaty_backup=NULL;
 bh->story_file=NULL;
 bh->story_file_extent=0;
 bh->story_file_blorbed=NULL;
 bh->story_file_blorbed_extent=0;
 bh->format_name=NULL;
 bh->story_file_extent=extent;
 bh->auth=1;
 bh->story_file=my_malloc(bh->story_file_extent,"story file storage");
 memcpy(bh->story_file,sf,extent);

 b=deeper_babel_init(NULL, bhp);
 if (b) bh->format_name=strdup(b);
 return b;
}
