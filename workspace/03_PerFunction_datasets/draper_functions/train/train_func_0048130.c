verify_hdr(struct cache_header *hdr, unsigned long size)
{
	git_SHA_CTX c;
	unsigned char sha1[20];

	if (hdr->hdr_signature != htonl(CACHE_SIGNATURE))
		return error("bad signature");
	if (hdr->hdr_version != htonl(2))
		return error("bad index version");
	git_SHA1_Init(&c);
	git_SHA1_Update(&c, hdr, size - 20);
	git_SHA1_Final(sha1, &c);
	if (hashcmp(sha1, (unsigned char *)hdr + size - 20))
		return error("bad index file sha1 signature");
	return 0;
}
