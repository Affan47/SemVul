dy_free_rcu(struct rcu_head *rcu)
{
	struct au_dykey *key;

	key = container_of(rcu, struct au_dykey, dk_rcu);
	DyPrSym(key);
	kfree(key);
}
