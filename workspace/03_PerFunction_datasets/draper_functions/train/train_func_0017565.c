ResizeTable(register XmtHashTable ht, Boolean grow)
#else
static void ResizeTable(ht, grow)
register XmtHashTable ht;
Boolean grow;
#endif
{
    Bucket **otable;
    long otablesize;
    register Bucket *bucket, *next, **head;
    register long i;

    otable = ht->table;
    otablesize =  1 << ht->size;

    if (grow) ht->size++;
    else if (ht->size > 2) ht->size--;
    else return;

    ht->table = (Bucket **) XtCalloc(1<<ht->size, sizeof(Bucket *));
    ht->mask = (1<<ht->size) - 1;

    for(i=0; i < otablesize; i++) {
	for(bucket = otable[i]; bucket; bucket = next) {
	    next = bucket->next;
	    head = &Hash(ht, bucket->key);
	    bucket->next = *head;
	    *head = bucket;
	}
    }
    XtFree((char *) otable);
}
