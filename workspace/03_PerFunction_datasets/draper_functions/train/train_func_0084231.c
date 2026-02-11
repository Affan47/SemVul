PSDictFree(struct psdict *dict) {
    int i;

    if ( dict==NULL )
return;
    for ( i=0; i<dict->next; ++i ) {
	if ( dict->keys!=NULL ) free(dict->keys[i]);
	free(dict->values[i]);
    }
    free(dict->keys);
    free(dict->values);
    free(dict);
}
