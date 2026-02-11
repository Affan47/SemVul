XmtHashTableDestroy(XmtHashTable ht)
#else
void XmtHashTableDestroy(ht)
XmtHashTable ht;
#endif
{
    register long i;
    register Bucket *bucket, *next;

    for(i=0; i < ht->mask+1; i++) {
	for (bucket = ht->table[i]; bucket; bucket = next) {
	    next = bucket->next;
	    XtFree((char *)bucket);
	}
    }
    XtFree((char *) ht->table);
    XtFree((char *) ht);
}
