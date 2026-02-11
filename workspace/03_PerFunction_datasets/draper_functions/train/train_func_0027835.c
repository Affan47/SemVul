env_add(char_array *env, const char *key, size_t key_len, const char *val, size_t val_len) {
	char *dst;
	size_t i;

	if (!key || !val) return -1;

	dst = malloc(key_len + val_len + 3);
	memcpy(dst, key, key_len);
	dst[key_len] = '=';

	memcpy(dst + key_len + 1, val, val_len + 1);

	for (i = 0; i < env->used; i++) {
		if (0 == strncmp(dst, env->ptr[i], key_len + 1)) {


			env->ptr[i] = dst;
			return 0;
		}
	}

	if (env->size == 0) {
		env->size = 16;
		env->ptr = malloc(env->size * sizeof(*env->ptr));
	} else if (env->size == env->used) {
		env->size += 16;
		env->ptr = realloc(env->ptr, env->size * sizeof(*env->ptr));
	}

	env->ptr[env->used++] = dst;

	return 0;
}
