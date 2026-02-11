PListOutputIntArray(FILE *plist, char *key, char *entries, int len) {
    int i;

    fprintf( plist, "\t<key>%s</key>\n", key );
    fprintf( plist, "\t<array>\n" );
    for ( i=0; i<len; ++i )
	fprintf( plist, "\t\t<integer>%d</integer>\n", entries[i] );
    fprintf( plist, "\t</array>\n" );
}
