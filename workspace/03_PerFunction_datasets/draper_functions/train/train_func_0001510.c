OTLookupFree(OTLookup *lookup) {
    struct lookup_subtable *st, *stnext;

    free(lookup->lookup_name);
    FeatureScriptLangListFree(lookup->features);
    for ( st=lookup->subtables; st!=NULL; st=stnext ) {
	stnext = st->next;
	free(st->subtable_name);
	free(st->suffix);
	chunkfree(st,sizeof(struct lookup_subtable));
    }
    chunkfree( lookup,sizeof(OTLookup) );
}
