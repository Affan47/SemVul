ImageCacheReload(void) {
    int i,k;
    struct image_bucket *bucket;
    char *path=NULL;
    int pathlen;
    GImage *temp, hold;

    ImagePathDefault();


    pathlen = imagepathlenmax+270; path = galloc(pathlen);
    for ( i=0; i<IC_SIZE; ++i ) {
	for ( bucket = imagecache[i]; bucket!=NULL; bucket=bucket->next ) {
	    if ( strlen(bucket->filename)+imagepathlenmax+3 > pathlen ) {
		pathlen = strlen(bucket->filename)+imagepathlenmax+20;
		path = grealloc(path,pathlen);
	    }
	    for ( k=0; imagepath[k]!=NULL; ++k ) {
		sprintf( path,"%s/%s", imagepath[k], bucket->filename );
		temp = GImageRead(path);
		if ( temp!=NULL )
	    break;
	    }
	    if ( temp!=NULL ) {
		if ( bucket->image==NULL )
		    bucket->image = temp;
		else {


		    hold = *(bucket->image);
		    *bucket->image = *temp;
		    *temp = hold;
		    GImageDestroy(temp);
		}
		free( bucket->absname );
		bucket->absname = copy( path );
	    }
	}
    }
    free(path);
}
