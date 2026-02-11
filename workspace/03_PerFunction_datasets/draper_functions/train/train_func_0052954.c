rbdir_node_count(DirEntry entry)
{
	gfarm_off_t lc, rc;

	lc = RB_LEFT (entry, node) == NULL ? 0 : RB_LEFT (entry, node)->nentries;
	rc = RB_RIGHT(entry, node) == NULL ? 0 : RB_RIGHT(entry, node)->nentries;
	return (lc + rc + 1);
}
