ebitmap_write(struct ebitmap *e, void *fp)
{
	struct ebitmap_node *n;
	u32 count;
	__le32 buf[3];
	u64 map;
	int bit, last_bit, last_startbit, rc;

	buf[0] = cpu_to_le32(BITS_PER_U64);

	count = 0;
	last_bit = 0;
	last_startbit = -1;
	ebitmap_for_each_positive_bit(e, n, bit) {
		if (rounddown(bit, (int)BITS_PER_U64) > last_startbit) {
			count++;
			last_startbit = rounddown(bit, BITS_PER_U64);
		}
		last_bit = roundup(bit + 1, BITS_PER_U64);
	}
	buf[1] = cpu_to_le32(last_bit);
	buf[2] = cpu_to_le32(count);

	rc = put_entry(buf, sizeof(u32), 3, fp);
	if (rc)
		return rc;

	map = 0;
	last_startbit = INT_MIN;
	ebitmap_for_each_positive_bit(e, n, bit) {
		if (rounddown(bit, (int)BITS_PER_U64) > last_startbit) {
			__le64 buf64[1];


			if (!map) {
				last_startbit = rounddown(bit, BITS_PER_U64);
				map = (u64)1 << (bit - last_startbit);
				continue;
			}


			buf[0] = cpu_to_le32(last_startbit);
			rc = put_entry(buf, sizeof(u32), 1, fp);
			if (rc)
				return rc;

			buf64[0] = cpu_to_le64(map);
			rc = put_entry(buf64, sizeof(u64), 1, fp);
			if (rc)
				return rc;


			map = 0;
			last_startbit = rounddown(bit, BITS_PER_U64);
		}
		map |= (u64)1 << (bit - last_startbit);
	}

	if (map) {
		__le64 buf64[1];


		buf[0] = cpu_to_le32(last_startbit);
		rc = put_entry(buf, sizeof(u32), 1, fp);
		if (rc)
			return rc;

		buf64[0] = cpu_to_le64(map);
		rc = put_entry(buf64, sizeof(u64), 1, fp);
		if (rc)
			return rc;
	}
	return 0;
}
