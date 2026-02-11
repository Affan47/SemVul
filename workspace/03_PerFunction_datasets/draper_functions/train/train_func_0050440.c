fs_rid_set_new()
{
    fs_rid_set *s = calloc(1, sizeof(fs_rid_set));
    for (int i=0; i<FS_RID_SET_ENTRIES; i++) {
	s->entry[i].val = FS_RID_NULL;
    }

    return s;
}
