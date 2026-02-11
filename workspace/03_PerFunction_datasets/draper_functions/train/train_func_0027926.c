compareSum(md5byte const *buf, unsigned long size, const unsigned char digest[16])
{
	unsigned char buf_digest[16];
	computeSum(buf, size, buf_digest);
	if (memcmp(digest, buf_digest, 16) != 0)
		return false;

	return true;
}
