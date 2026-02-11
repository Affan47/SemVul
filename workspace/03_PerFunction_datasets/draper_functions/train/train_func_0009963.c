rpm_getcount(int tag)
{
	rpm_index **found;
	found = bsearch(&tag, mytags, tagcount, sizeof(struct rpmtag *), bsearch_rpmtag);
	if (!found)
		return 0;
	return found[0]->count;
}
