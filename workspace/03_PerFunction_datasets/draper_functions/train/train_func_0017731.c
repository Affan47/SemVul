_GGadgetImageCache(char *filename, char **foundname) {
    int index = hash_filename(filename);
    struct image_bucket *bucket;
    char *path;
    int k;

    for ( bucket = imagecache[index]; bucket!=NULL; bucket = bucket->next ) {
	if ( strcmp(bucket->filename,filename)==0 ) {
	    if ( foundname!=NULL ) *foundname = copy( bucket->absname );
return( bucket->image );
	}
    }
    bucket = gcalloc(1,sizeof(struct image_bucket));
    bucket->next = imagecache[index];
    imagecache[index] = bucket;
    bucket->filename = copy(filename);

    ImagePathDefault();

    path = galloc(strlen(filename)+imagepathlenmax+10 );
    for ( k=0; imagepath[k]!=NULL; ++k ) {
	sprintf( path,"%s/%s", imagepath[k], filename );
	bucket->image = GImageRead(path);
	if ( bucket->image!=NULL ) {
	    bucket->absname = copy(path);
    break;
	}
    }
    free(path);
    if ( bucket->image!=NULL ) {

	struct _GImage *base = bucket->image->u.image;
	if ( base->image_type==it_mono && base->clut==NULL )
	    base->trans = 1;
	else if ( base->image_type!=it_true && base->clut!=NULL && base->trans==0xffffffff ) {
	    int i;
	    for ( i=0 ; i<base->clut->clut_len; ++i ) {
		if ( base->clut->clut[i]==0xffffff ) {
		    base->trans = i;
	    break;
		}
	    }
	}
    }
    if ( foundname!=NULL && bucket->image!=NULL )
	*foundname = copy( bucket->absname );
return( bucket->image );
}
