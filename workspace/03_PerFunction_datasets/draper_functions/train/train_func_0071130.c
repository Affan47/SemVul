perminit_ip(DES_KEY * key)
{
	register int l, j, k;
	int i, m;


	memset(key->iperm, '\0', 16 * 16 * 8);

	for (i = 0; i < 16; i++)
		for (j = 0; j < 16; j++)
			for (k = 0; k < 64; k++) {
				l = ip[k] - 1;
				if ((l >> 2) != i)
					continue;
				if (!(j & nibblebit[l & 3]))
					continue;
				m = k & 07;
				key->iperm[i][j][k >> 3] |= bytebit[m];
			}
}
