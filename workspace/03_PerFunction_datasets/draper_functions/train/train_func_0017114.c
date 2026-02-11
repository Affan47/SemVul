worker(void *arg)
{
	SHA_CTX		hash, copy;
	RSA		*rsa;
	uint8_t		*tmp, *der,
			buf[SHA_DIGEST_LENGTH],
			onion[ONION_LENP1],
			onionfinal[ONION_LENP1];
	signed int	derlen;
	uint64_t	*counter;

	unsigned int	e, e_be;

	counter = (uint64_t *)arg;

	while (!done) {

		rsa = RSA_generate_key(RSA_KEYS_BITLEN, RSA_E_START,
		    NULL, NULL);
		if (!rsa)
			error("RSA Key Generation failed!\n");


		if((derlen = i2d_RSAPublicKey(rsa, NULL)) < 0)
			error("DER encoding failed!\n");
		if ((der = tmp = (uint8_t *)malloc(derlen)) == NULL)
			error("malloc(derlen) failed!\n");
		if (i2d_RSAPublicKey(rsa, &tmp) != derlen)
			error("DER encoding failed!\n");


		SHA1_Init(&hash);
		SHA1_Update(&hash, der, derlen - SIZE_OF_E);
		free(der);
		e = RSA_E_START - 2;


		while  ((e < RSA_E_LIMIT) && !done) {
			e += 2;

			e_be = HTOBE32(e);

			memcpy(&copy, &hash, SHA_REL_CTX_LEN);
			copy.num = hash.num;

			SHA1_Update(&copy, &e_be, SIZE_OF_E);
			SHA1_Final(buf, &copy);
			(*counter)++;

			base32_enc(onion, buf);


			if (search(buf, onion)) {


				if (!BN_bin2bn((uint8_t *)&e_be, SIZE_OF_E, rsa->e))
					error("Failed to set e in RSA key!\n");
				if (!validkey(rsa))
					error("A bad key was found!\n");
				if (pflag)
					onion[prefixlen] = '\0';

				onion_enc(onionfinal, rsa);


				if (strncmp((char *)onion, (char *)onionfinal,
				    (!rflag ? strnlen((char *)onion, ONION_LENP1) : 16))) {
					msg("\nWARNING! Error detected! CPU/RAM overheating?\n");
					msg("Found %s, but finalized to %s.\n",
					    (char *)onion, (char *)onionfinal);
					msg("Suspending this thread for 30 seconds.\n");
					sleep(30);
					msg("Generating new RSA key.\n\n");
					break;
				} else
					printresult(rsa, onion, onionfinal);

				if (!cflag)
					done = 1;
				break;
			}
		}
		RSA_free(rsa);
	}
	return 0;
}
