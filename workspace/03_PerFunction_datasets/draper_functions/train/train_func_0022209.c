crypt_all(int *pcount, struct db_salt *salt)
{
	static int warned = 0;
	int count = *pcount;
	int index;

#if defined(_OPENMP) && defined(__GLIBC__)
#pragma omp parallel for default(none) private(index) shared(warned, count, crypt_out, saved_key, saved_salt, crypt_data, stderr)
	for (index = 0; index < count; index++) {
		char *hash;
		int t = omp_get_thread_num();
		if (t < MAX_THREADS) {
			struct crypt_data **data = &crypt_data[t];
			if (!*data) {

				size_t mask = MEM_ALIGN_PAGE, shift = 0;
				while (t) {
					mask >>= 1;
					if (mask < MEM_ALIGN_CACHE)
						break;
					if (t & 1)
						shift += mask;
					t >>= 1;
				}
				*data = (void *)((char *)
				    mem_alloc_tiny(sizeof(**data) +
				    shift, MEM_ALIGN_PAGE) + shift);
				memset(*data, 0, sizeof(**data));
			}
			hash = crypt_r(saved_key[index], saved_salt, *data);
		} else {
			struct crypt_data data;
			memset(&data, 0, sizeof(data));
			hash = crypt_r(saved_key[index], saved_salt, &data);
		}
		if (!hash) {
#pragma omp critical
			if (!warned) {
				fprintf(stderr,
				    "Warning: crypt_r() returned NULL\n");
				warned = 1;
			}
			hash = "";
		}
		strnzcpy(crypt_out[index], hash, BINARY_SIZE);
	}
#else
#if defined(_OPENMP) && defined(__sun)


#pragma omp parallel for default(none) private(index) shared(warned, count, crypt_out, saved_key, saved_salt, stderr)
#endif
	for (index = 0; index < count; index++) {
		char *hash = crypt(saved_key[index], saved_salt);
		if (!hash) {
#if defined(_OPENMP) && defined(__sun)
#pragma omp critical
#endif
			if (!warned) {
				fprintf(stderr,
				    "Warning: crypt() returned NULL\n");
				warned = 1;
			}
			hash = "";
		}
		strnzcpy(crypt_out[index], hash, BINARY_SIZE);
	}
#endif

	return count;
}
