siphash24_mix(u64 &v0, u64 &v1, u64 &v2, u64 &v3, const void *input, const u64 input_len, u64 xor_val) {

	const u64 *m64 = (const u64 *)input;
	u64 words = input_len >> 3;
	while (words > 0) {
		u64 mi = read64(m64++);

		v3 ^= mi;
		SIP_DOUBLE_ROUND(v0, v1, v2, v3);
		v0 ^= mi;

		--words;
	}


	const u8 *m = reinterpret_cast<const u8 *>( m64 );
	u64 last7 = input_len << 56;
	switch (input_len & 7) {
	case 7: last7 |= (u64)m[6] << 48;
	case 6: last7 |= (u64)m[5] << 40;
	case 5: last7 |= (u64)m[4] << 32;
	case 4: last7 |= read32(m);
		break;
	case 3: last7 |= (u64)m[2] << 16;
	case 2: last7 |= (u64)m[1] << 8;
	case 1: last7 |= (u64)m[0];
		break;
	};


	v3 ^= last7;
	SIP_DOUBLE_ROUND(v0, v1, v2, v3);
	v0 ^= last7;

	v2 ^= xor_val;
	SIP_DOUBLE_ROUND(v0, v1, v2, v3);
	SIP_DOUBLE_ROUND(v0, v1, v2, v3);
}
