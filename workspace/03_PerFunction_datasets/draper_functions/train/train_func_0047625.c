aes_encrypt(std::ifstream& in, std::ofstream& out, std::string passphrase)
{
	int size;
	gcry_cipher_hd_t handle;
	gcry_error_t ret;


	in.seekg(0, std::ios::end);
	size = in.tellg();
	size = (size % BLOCK_SZ)? (size + (BLOCK_SZ - size % BLOCK_SZ)) : size;


	char *plain = new char[size];
	char *cipher = new char[size];


	in.seekg(0, std::ios::beg);
	std::streambuf* raw_buffer = in.rdbuf();
	raw_buffer->sgetn(plain, size);

	init_gcrypt_key_iv(handle, passphrase, std::string(""));

	ret = gcry_cipher_encrypt(handle, (unsigned char *)&cipher[0], size,
		(unsigned char *)&plain[0], size);
	DIE(ret, "gcry_cipher_encrypt");

	gcry_cipher_close(handle);
	out << cipher;

	delete [] plain;
	delete [] cipher;
}
