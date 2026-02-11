zSetHash (zHash *hash, const char *key, void *val) {
	int i, index;
	char *string;
	char *actual_key;


	int new_key = 1;

	index = zHashFunc(hash, key);


	for (i = 0; i < hash->key[index].size; i++) {
		string = hash->key[index].elem[i];
		if (strcmp(key, string) == 0) {
			hash->val[index].elem[i] = val;
			new_key = 0;
			break;
		}
	}

	if (new_key) {
		actual_key = (char*) zMalloc(sizeof(char)*(strlen(key) + 1), "zSetHash for key copy");
		strcpy(actual_key, key);
		zPushVec(&hash->val[index], val);
		zPushVec(&hash->key[index], (void*)actual_key);
		hash->keys++;
	}


	if ((float)hash->keys / (float)hash->slots >= zMAX_HASH_DEPTH) {
		zExpandHash(hash);
	}
}
