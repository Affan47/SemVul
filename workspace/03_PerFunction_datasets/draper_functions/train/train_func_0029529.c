__bch_extent_invalid(struct cache_set *c, const struct bkey *k)
{
	char buf[80];

	if (!KEY_SIZE(k))
		return true;

	if (KEY_SIZE(k) > KEY_OFFSET(k))
		goto bad;

	if (__ptr_invalid(c, k))
		goto bad;

	return false;
bad:
	bch_extent_to_text(buf, sizeof(buf), k);
	cache_bug(c, "spotted extent %s: %s", buf, bch_ptr_status(c, k));
	return true;
}
