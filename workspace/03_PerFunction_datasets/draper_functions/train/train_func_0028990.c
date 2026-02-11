au_nhash_test_longer_wh(struct au_nhash *whlist, aufs_bindex_t btgt,
			    int limit)
{
	int num;
	unsigned int u, n;
	struct hlist_head *head;
	struct au_vdir_wh *pos;

	num = 0;
	n = whlist->nh_num;
	head = whlist->nh_head;
	for (u = 0; u < n; u++, head++)
		hlist_for_each_entry(pos, head, wh_hash)
			if (pos->wh_bindex == btgt && ++num > limit)
				return 1;
	return 0;
}
