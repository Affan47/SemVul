MarkSetFree(int cnt,char **classes,char **names) {
    int i;

    for ( i=0; i<cnt; ++i ) {
	free( classes[i] );
	free( names[i] );
    }
    free( classes );
    free( names );
}
