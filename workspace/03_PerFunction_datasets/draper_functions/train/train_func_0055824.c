print_msg(struct uocrypt_enc_msg * msg) {
	if(msg == NULL) {
		printf("Null message.\n");
	} else {
		printf("IV:\t");
		for(size_t i = 0; i < UOCRYPT_BLOCK_LEN; ++i) {
			printf("%02X", msg->iv[i]);
		}
		printf("\nText:\t");
		for(size_t i = 0; i < msg->txtlen; ++i) {
			printf("%02X", msg->txt[i]);
		}
		printf("\n");
	}
}
