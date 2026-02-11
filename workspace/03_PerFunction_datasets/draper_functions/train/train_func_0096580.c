fs_rid_set_add(fs_rid_set *s, fs_rid val)
{
    if (val == FS_RID_NULL) return;

    struct rid_entry *e = &s->entry[FS_RID_ENTRY_HASH(val)];
    if (e->val == val) return;
    if (e->val == FS_RID_NULL) {
	e->val = val;

	return;
    }
    while (e->next) {
	if (e->val == val) return;
	e = e->next;
    }

    struct rid_entry *ne = calloc(1, sizeof(struct rid_entry));
    ne->val = val;
    e->next = ne;
}
