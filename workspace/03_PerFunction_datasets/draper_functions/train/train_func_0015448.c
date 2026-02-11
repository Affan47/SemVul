loginUsingCRAMMD5(const std::string& username, const std::string& password)
{
	HMACEngine<MD5Engine> hmac(password);
	loginUsingCRAM(username, "CRAM-MD5", hmac);
}
