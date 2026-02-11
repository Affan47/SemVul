sign_verify_reply(struct ncp_server *server, const char *packet, size_t size, __u32 totalsize, const void *sign_buff) {
	unsigned char data[64];
	unsigned char hash[16];

	memcpy(data, server->sign_root, 8);
	*(__u32*)(data + 8) = totalsize;
	if (size < 52) {
		memcpy(data + 12, packet, size);
		memset(data + 12 + size, 0, 52 - size);
	} else {
		memcpy(data + 12, packet, 52);
	}
	nwsign(server->sign_last, data, hash);
	return memcmp(sign_buff, hash, 8);
}
