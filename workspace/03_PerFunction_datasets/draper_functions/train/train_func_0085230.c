BaseLangCopy(struct baselangextent *extent) {
    struct baselangextent *head, *last, *cur;

    last = head = NULL;
    for ( ; extent!=NULL; extent = extent->next ) {
	cur = chunkalloc(sizeof(struct baselangextent));
	*cur = *extent;
	cur->features = BaseLangCopy(cur->features);
	if ( head==NULL )
	    head = cur;
	else
	    last->next = cur;
	last = cur;
    }
return( head );
}
