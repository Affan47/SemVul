acl_compare(const sockaddr_t *a1, const sockaddr_t *a2)
{
	int ret = 0;
	uint32_t mask = 0xffffffff;
	short mask_bits = a1->prefix;
	const short chunk_bits = sizeof(mask) * CHAR_BIT;


	if (a1->len != a2->len) {
		if (a1->len < a2->len)
			return -1;
		else
			return 1;
	}


	unsigned i = 0;
	while (ret == 0 && mask_bits > 0) {

		if (mask_bits <= chunk_bits) {
			mask = acl_fill_mask32(mask_bits);
			mask_bits = 0;
		} else {
			mask_bits -= chunk_bits;
		}


		if (mask > 0)
			ret = cmp_chunk(a1, a2, i, mask);
		++i;
	}

	return ret;
}
