fs_rid_vector_append_set(fs_rid_vector *v, fs_rid_set *s)
{
    if (!s) return;

    for (int hash=0; hash < FS_RID_SET_ENTRIES; hash++) {
	for (struct rid_entry *e=&(s->entry[hash]); e; e=e->next) {
	    if (e->val != FS_RID_NULL) {
		fs_rid_vector_append(v, e->val);
	    }
	}
    }
}
