huge_sha1_extract32(const char *buf, size_t len, struct sha1 *sha1,
	const struct gnutella_node *n)
{
	if (len != SHA1_BASE32_SIZE || huge_improbable_sha1(buf, len))
		goto bad;

	if (SHA1_RAW_SIZE != base32_decode(sha1->data, sizeof sha1->data, buf, len))
		goto bad;


	if (huge_improbable_sha1(sha1->data, sizeof sha1->data)) {
		if (GNET_PROPERTY(share_debug)) {
			if (is_printable(buf, len)) {
				g_warning("%s has improbable SHA1 (len=%lu): %.*s, hex: %s",
					gmsg_node_infostr(n),
					(unsigned long) len,
					(int) MIN(len, (size_t) INT_MAX),
					buf, data_hex_str(sha1->data, sizeof sha1->data));
			} else
				goto bad;
		}
		return FALSE;
	}

	return TRUE;

bad:
	if (GNET_PROPERTY(share_debug)) {
		if (is_printable(buf, len)) {
			g_warning("%s has bad SHA1 (len=%u): %.*s",
				gmsg_node_infostr(n),
				(unsigned) len,
				(int) MIN(len, (size_t) INT_MAX),
				buf);
		} else {
			g_warning("%s has bad SHA1 (len=%u)",
				gmsg_node_infostr(n), (unsigned) len);
			if (len)
				dump_hex(stderr, "Base32 SHA1", buf, len);
		}
	}

	return FALSE;
}
