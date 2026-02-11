chap_md5_verify_response(int id, char *name,
			 unsigned char *secret, int secret_len,
			 unsigned char *challenge, unsigned char *response,
			 char *message, int message_space)
{
	MD5_CTX ctx;
	unsigned char idbyte = id;
	unsigned char hash[MD5_HASH_SIZE];
	int challenge_len, response_len;

	challenge_len = *challenge++;
	response_len = *response++;
	if (response_len == MD5_HASH_SIZE) {

		MD5_Init(&ctx);
		MD5_Update(&ctx, &idbyte, 1);
		MD5_Update(&ctx, secret, secret_len);
		MD5_Update(&ctx, challenge, challenge_len);
		MD5_Final(hash, &ctx);


		if (memcmp(hash, response, MD5_HASH_SIZE) == 0) {
			slprintf(message, message_space, "Access granted");
			return 1;
		}
	}
	slprintf(message, message_space, "Access denied");
	return 0;
}
