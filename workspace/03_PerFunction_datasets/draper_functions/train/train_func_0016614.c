asn1_tag_decode(struct asn1_ctx *ctx, unsigned int *tag)
{
	unsigned char ch;

	*tag = 0;

	do {
		if (!asn1_octet_decode(ctx, &ch))
			return 0;
		*tag <<= 7;
		*tag |= ch & 0x7F;
	} while ((ch & 0x80) == 0x80);
	return 1;
}
