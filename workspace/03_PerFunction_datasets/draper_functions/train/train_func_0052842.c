process_key(struct crypt_device *cd, const char *hash_name,
			 const char *key_file, size_t key_size,
			 const char *pass, size_t passLen)
{
	char *key = safe_alloc(key_size);
	memset(key, 0, key_size);


	if (key_file && strcmp(key_file, "-")) {
		if(passLen < key_size) {
			log_err(cd, _("Cannot not read %d bytes from key file %s.\n"),
				key_size, key_file);
			safe_free(key);
			return NULL;
		}
		memcpy(key, pass, key_size);
		return key;
	}


	if (hash_name) {
		if (hash(NULL, hash_name, key, key_size, pass, passLen) < 0) {
			log_err(cd, _("Key processing error (using hash algorithm %s).\n"),
				hash_name);
			safe_free(key);
			return NULL;
		}
	} else if (passLen > key_size) {
		memcpy(key, pass, key_size);
	} else {
		memcpy(key, pass, passLen);
	}

	return key;
}
