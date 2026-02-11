fr_rand_seed(const void *data, size_t size)
{
	uint32_t hash;


	if (!fr_rand_initialized) {
		int fd;

		memset(&fr_rand_pool, 0, sizeof(fr_rand_pool));

		fd = open("/dev/urandom", O_RDONLY);
		if (fd >= 0) {
			size_t total;
			ssize_t this;

			total = 0;
			while (total < sizeof(fr_rand_pool.randrsl)) {
				this = read(fd, fr_rand_pool.randrsl,
					    sizeof(fr_rand_pool.randrsl) - total);
				if ((this < 0) && (errno != EINTR)) break;
				if (this > 0) total += this;
 			}
			close(fd);
		} else {
			fr_rand_pool.randrsl[0] = fd;
			fr_rand_pool.randrsl[1] = time(NULL);
			fr_rand_pool.randrsl[2] = errno;
		}

		fr_randinit(&fr_rand_pool, 1);
		fr_rand_pool.randcnt = 0;
		fr_rand_initialized = 1;
	}

	if (!data) return;


	hash = fr_rand();
	if (!hash) hash = fr_rand();
	hash = fr_hash_update(data, size, hash);

	fr_rand_pool.randmem[fr_rand_pool.randcnt] ^= hash;
}
