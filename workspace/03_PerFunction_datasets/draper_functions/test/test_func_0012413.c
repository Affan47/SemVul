RC4(RC4_KEY *rc4_key, unsigned char *plaintext, int *plaintext_length, unsigned char *ciphertext){
    int i = 0, j = 0, n, temp;

    for (i = 0; i < *plaintext_length; i++){
	i = (i + 1) % 256;
	j = (j + rc4_key -> S[i]) % 256;

	temp = rc4_key -> S[i];
	rc4_key -> S[i] = rc4_key -> S[j];
	rc4_key -> S[j] = temp;

	n = rc4_key -> S[(rc4_key -> S[i] + rc4_key -> S[j]) % 256];


	*(ciphertext + i) = *(plaintext + i) ^ n;
    }
}
