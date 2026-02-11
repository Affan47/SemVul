parse_commit_buffer(struct commit *item, void *buffer, unsigned long size)
{
	char *tail = buffer;
	char *bufptr = buffer;
	unsigned char parent[20];
	struct commit_list **pptr;
	struct commit_graft *graft;
	unsigned n_refs = 0;

	if (item->object.parsed)
		return 0;
	item->object.parsed = 1;
	tail += size;
	if (tail <= bufptr + 5 || memcmp(bufptr, "tree ", 5))
		return error("bogus commit object %s", sha1_to_hex(item->object.sha1));
	if (tail <= bufptr + 45 || get_sha1_hex(bufptr + 5, parent) < 0)
		return error("bad tree pointer in commit %s",
			     sha1_to_hex(item->object.sha1));
	item->tree = lookup_tree(parent);
	if (item->tree)
		n_refs++;
	bufptr += 46;
	pptr = &item->parents;

	graft = lookup_commit_graft(item->object.sha1);
	while (bufptr + 48 < tail && !memcmp(bufptr, "parent ", 7)) {
		struct commit *new_parent;

		if (tail <= bufptr + 48 ||
		    get_sha1_hex(bufptr + 7, parent) ||
		    bufptr[47] != '\n')
			return error("bad parents in commit %s", sha1_to_hex(item->object.sha1));
		bufptr += 48;
		if (graft)
			continue;
		new_parent = lookup_commit(parent);
		if (new_parent) {
			pptr = &commit_list_insert(new_parent, pptr)->next;
			n_refs++;
		}
	}
	if (graft) {
		int i;
		struct commit *new_parent;
		for (i = 0; i < graft->nr_parent; i++) {
			new_parent = lookup_commit(graft->parent[i]);
			if (!new_parent)
				continue;
			pptr = &commit_list_insert(new_parent, pptr)->next;
			n_refs++;
		}
	}
	item->date = parse_commit_date(bufptr);

	if (track_object_refs) {
		unsigned i = 0;
		struct commit_list *p;
		struct object_refs *refs = alloc_object_refs(n_refs);
		if (item->tree)
			refs->ref[i++] = &item->tree->object;
		for (p = item->parents; p; p = p->next)
			refs->ref[i++] = &p->item->object;
		set_object_refs(&item->object, refs);
	}

	return 0;
}
