__gbt_merkleroot(struct pool *pool, unsigned char *merkle_root)
{
	unsigned char merkle_sha[64];
	int i;

	gen_hash(pool->coinbase, merkle_root, pool->coinbase_len);
	memcpy(merkle_sha, merkle_root, 32);
	for (i = 0; i < pool->merkles; i++) {
		memcpy(merkle_sha + 32, pool->merklebin + i * 32, 32);
		gen_hash(merkle_sha, merkle_root, 64);
		memcpy(merkle_sha, merkle_root, 32);
	}
}
