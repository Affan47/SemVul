FcObjectFini (void)
{
    int		    i;
    FcObjectBucket  *b, *next;

    for (i = 0; i < OBJECT_HASH_SIZE; i++)
    {
	for (b = FcObjectBuckets[i]; b; b = next)
	{
	    next = b->next;
	    free (b);
	}
	FcObjectBuckets[i] = 0;
    }
    for (i = 0; i < FcObjectsNumber; i++)
	if (FcObjects[i].type == -1)
	    free ((void*) FcObjects[i].object);
    if (FcObjects != _FcBaseObjectTypes)
	free (FcObjects);
    FcObjects = (FcObjectType *) _FcBaseObjectTypes;
    FcObjectsNumber = NUM_OBJECT_TYPES;
    FcObjectsSize = 0;
    FcObjectsInited = FcFalse;
}
