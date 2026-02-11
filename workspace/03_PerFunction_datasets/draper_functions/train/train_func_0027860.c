replace_lkey(struct tree_balance *tb, int h, struct item_head *key)
{
	RFALSE(tb->L[h] == NULL || tb->CFL[h] == NULL,
	       "L[h](%p) and CFL[h](%p) must exist in replace_lkey",
	       tb->L[h], tb->CFL[h]);

	if (B_NR_ITEMS(PATH_H_PBUFFER(tb->tb_path, h)) == 0)
		return;

	memcpy(internal_key(tb->CFL[h], tb->lkey[h]), key, KEY_SIZE);

	do_balance_mark_internal_dirty(tb, tb->CFL[h], 0);
}
