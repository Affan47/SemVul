create_cw_keys(SKey *k)
{
	if (!k->key[0])
		k->key[0] = k->op->create_cwkey();
	if (!k->key[1])
		k->key[1] = k->op->create_cwkey();
}
