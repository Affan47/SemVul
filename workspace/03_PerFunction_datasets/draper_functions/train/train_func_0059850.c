mark_reachable(struct object *obj, unsigned int mask)
{
	const struct object_refs *refs;

	if (!track_object_refs)
		die("cannot do reachability with object refs turned off");

	if (obj->flags & mask)
		return;
	obj->flags |= mask;
	refs = lookup_object_refs(obj);
	if (refs) {
		unsigned i;
		for (i = 0; i < refs->count; i++)
			mark_reachable(refs->ref[i], mask);
	}
}
