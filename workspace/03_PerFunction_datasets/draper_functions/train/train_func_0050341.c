FcSharedStrFree (const FcChar8 *name)
{
    FcChar32		hash = FcStringHash (name);
    struct objectBucket	**p;
    struct objectBucket	*b;
    int			size;

    for (p = &FcObjectBuckets[hash % OBJECT_HASH_SIZE]; (b = *p); p = &(b->next))
	if (b->hash == hash && ((char *)name == (char *) (b + 1)))
	{
	    b->ref_count--;
	    if (!b->ref_count)
	    {
		*p = b->next;
		size = sizeof (struct objectBucket) + strlen ((char *)name) + 1;
		size = (size + 3) & ~3;
		FcMemFree (FC_MEM_SHAREDSTR, size);
		free (b);
	    }
            return FcTrue;
	}
    return FcFalse;
}
