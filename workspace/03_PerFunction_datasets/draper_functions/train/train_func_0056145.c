computeAccept(const std::string& key)
{
	std::string accept(key);
	accept += WEBSOCKET_GUID;
	Poco::SHA1Engine sha1;
	sha1.update(accept);
	Poco::DigestEngine::Digest d = sha1.digest();
	std::ostringstream ostr;
	Poco::Base64Encoder base64(ostr);
	base64.write(reinterpret_cast<const char*>(&d[0]), d.size());
	base64.close();
	return ostr.str();
}
