recursively_fill_closest_from(
	const kuid_t *id,
	struct kbucket *kb,
	knode_t **kvec, int kcnt, const kuid_t *exclude, bool alive)
{
	int byt;
	uchar mask;
	struct kbucket *closest;
	int added;

	g_assert(id);
	g_assert(kb);

	if (is_leaf(kb))
		return fill_closest_in_bucket(id, kb, kvec, kcnt, exclude, alive);

	kuid_position(kb->depth, &byt, &mask);

	if ((kb->one->prefix.v[byt] & mask) == (id->v[byt] & mask)) {
		g_assert((kb->zero->prefix.v[byt] & mask) != (id->v[byt] & mask));
		closest = kb->one;
	} else {
		g_assert((kb->zero->prefix.v[byt] & mask) == (id->v[byt] & mask));
		closest = kb->zero;
	}

	added = recursively_fill_closest_from(
		id, closest, kvec, kcnt, exclude, alive);

	if (added < kcnt)
		added += recursively_fill_closest_from(id, sibling_of(closest),
			kvec + added, kcnt - added, exclude, alive);

	return added;
}
