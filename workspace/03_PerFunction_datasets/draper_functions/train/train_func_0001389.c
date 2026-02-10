_GIO_translateURL(unichar_t *path, enum giofuncs gf) {
    struct transtab *test;

    if ( transtab==NULL )
return( NULL );

    for ( test = transtab; test->old!=NULL; ++test ) {
	if ( (test->gf_mask&(1<<gf)) && u_strncmp(path,test->old,test->olen)==0 ) {
	    unichar_t *res = galloc((u_strlen(path)-test->olen+u_strlen(test->new)+1)*sizeof(unichar_t));
	    u_strcpy(res,test->new);
	    u_strcat(res,path+test->olen);
return( res );
	}
    }
return( NULL );
}
