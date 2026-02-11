keybuf_nonoverlapping_cmp(struct keybuf_key *l,
					    struct keybuf_key *r)
{
	return clamp_t(int64_t, bkey_cmp(&l->key, &r->key), -1, 1);
}
