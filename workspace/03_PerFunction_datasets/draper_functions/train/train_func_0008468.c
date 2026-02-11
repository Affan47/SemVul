_dxfGroup_Gather(Group g, struct gather *gather, struct tile *tile)
{
    Object o;
    int i;
    struct tile new;

    if (!parameters((Object)g, &new, tile)) return NULL;
    if (DXGetObjectClass((Object)g)==CLASS_COMPOSITEFIELD)
	new.ignore = 1;

    for (i=0; (o=DXGetEnumeratedMember(g, i, NULL)); i++) {
	DXDebug("G", "member %d", i);
	if (!_dxfGather(o, gather, &new))
	    return NULL;
    }

    return (Object) g;
}
