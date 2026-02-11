ksa(unsigned char key[], int key_len){
	for(i = 0;i < 256;i++){
		j = (j + key[i % key_len] + S[i]) % 256;
		intercambio(i, j);
	}

	i = 0;
	j = 0;
}
