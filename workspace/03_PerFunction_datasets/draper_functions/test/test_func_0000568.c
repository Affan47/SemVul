seckeys_create(kuid_t **svec, int scnt, const knode_t *kn)
{
	struct seckeys *sk;

	g_assert(svec);
	g_assert(scnt);
	knode_check(kn);

	WALLOC(sk);
	sk->skeys = svec;
	sk->kn = knode_refcnt_inc(kn);
	sk->scnt = scnt;
	sk->next_skey = 0;

	return sk;
}
