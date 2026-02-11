copy_wormhash(struct ebt_mac_wormhash *d,
			  const struct ebt_mac_wormhash *s)
{
	int dpoolsize = d->poolsize;
	int dsize, ssize, amount;

	dsize = ebt_mac_wormhash_size(d);
	ssize = ebt_mac_wormhash_size(s);
	amount = dsize < ssize ? dsize : ssize;
	memcpy(d, s, amount);
	d->poolsize = dpoolsize;
}
