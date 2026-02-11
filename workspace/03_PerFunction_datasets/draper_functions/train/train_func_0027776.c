growl_generate_authheader_alloc(const char*const password)
{
	char* salt;
    char* salthash;
    char* keyhash;
	char* authheader = NULL;

	if (password) {
		salt = gen_salt_alloc(8);
		keyhash = gen_password_hash_alloc(password, salt);
		salthash = string_to_hex_alloc(salt, 8);
		free(salt);
		authheader = (char*)malloc(strlen(keyhash) + strlen(salthash) + 7);
		sprintf(authheader, " MD5:%s.%s", keyhash, salthash);
		free(salthash);
		free(keyhash);
	}

	return authheader;
}
