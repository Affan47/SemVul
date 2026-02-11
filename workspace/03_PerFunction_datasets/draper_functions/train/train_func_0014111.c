keccak_theta(uint64_t *A)
{
	unsigned int x;
	uint64_t C[5], D[5];

	for (x = 0; x < 5; x++) {
		C[x] = A[x] ^ A[x + 5] ^ A[x + 10] ^ A[x + 15] ^ A[x + 20];
	}
	D[0] = ROTL64(C[1], 1) ^ C[4];
	D[1] = ROTL64(C[2], 1) ^ C[0];
	D[2] = ROTL64(C[3], 1) ^ C[1];
	D[3] = ROTL64(C[4], 1) ^ C[2];
	D[4] = ROTL64(C[0], 1) ^ C[3];

	for (x = 0; x < 5; x++) {
		A[x]      ^= D[x];
		A[x + 5]  ^= D[x];
		A[x + 10] ^= D[x];
		A[x + 15] ^= D[x];
		A[x + 20] ^= D[x];
	}
}
