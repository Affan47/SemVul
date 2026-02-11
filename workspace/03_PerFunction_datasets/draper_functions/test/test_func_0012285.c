zValsOfHash (const zHash *hash) {
	int i, j;
	zVec *vec;
	vec = zMalloc(sizeof(zVec), "zValsOfHash");

	zInitVec(vec, hash->keys);
	for (i = 0; i < hash->slots; i++) {
		for (j = 0; j < hash->val[i].size; j++) {
			zPushVec(vec, hash->val[i].elem[j]);
		}
	}
	return vec;
}
