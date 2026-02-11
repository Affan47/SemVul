freeptrtab(unsigned char **ptrtab,int tot) {
    int i,j;

    for ( i=0; i<tot; ++i )
	if ( ptrtab[i]!=NULL ) {
	    for ( j=i+1; j<tot; ++j )
		if ( ptrtab[j]==ptrtab[i] )
		    ptrtab[j] = NULL;
	    gfree(ptrtab[i]);
	}
}
