runtime_mapiterkey(struct hash_iter *it, void *ak)
{
	byte *res;
	Type *key;

	res = it->data;
	if(res == nil)
		return false;
	key = it->t->key;
	key->alg->copy(key->size, ak, res);
	return true;
}
