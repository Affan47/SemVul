isAPropertyOf(VObject *o, const char *id)
{
    VObjectIterator i;
    initPropIterator(&i,o);
    while (moreIteration(&i)) {
	VObject *each = nextVObject(&i);
	if (!strcasecmp(id,each->id))
	    return each;
	}
    return (VObject*)0;
}
