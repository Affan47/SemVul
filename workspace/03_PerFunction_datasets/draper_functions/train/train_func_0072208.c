ext2fs_dirhash(int version, const char *name, int len,
			 const __u32 *seed,
			 ext2_dirhash_t *ret_hash,
			 ext2_dirhash_t *ret_minor_hash)
{
	__u32	hash;
	__u32	minor_hash = 0;
	const char	*p;
	int		i;
	__u32 		in[8], buf[4];
	int		unsigned_flag = 0;


	buf[0] = 0x67452301;
	buf[1] = 0xefcdab89;
	buf[2] = 0x98badcfe;
	buf[3] = 0x10325476;


	if (seed) {
		for (i=0; i < 4; i++) {
			if (seed[i])
				break;
		}
		if (i < 4)
			memcpy(buf, seed, sizeof(buf));
	}

	switch (version) {
	case EXT2_HASH_LEGACY_UNSIGNED:
		unsigned_flag++;
	case EXT2_HASH_LEGACY:
		hash = dx_hack_hash(name, len, unsigned_flag);
		break;
	case EXT2_HASH_HALF_MD4_UNSIGNED:
		unsigned_flag++;
	case EXT2_HASH_HALF_MD4:
		p = name;
		while (len > 0) {
			str2hashbuf(p, len, in, 8, unsigned_flag);
			halfMD4Transform(buf, in);
			len -= 32;
			p += 32;
		}
		minor_hash = buf[2];
		hash = buf[1];
		break;
	case EXT2_HASH_TEA_UNSIGNED:
		unsigned_flag++;
	case EXT2_HASH_TEA:
		p = name;
		while (len > 0) {
			str2hashbuf(p, len, in, 4, unsigned_flag);
			TEA_transform(buf, in);
			len -= 16;
			p += 16;
		}
		hash = buf[0];
		minor_hash = buf[1];
		break;
	default:
		*ret_hash = 0;
		return EXT2_ET_DIRHASH_UNSUPP;
	}
	*ret_hash = hash & ~1;
	if (ret_minor_hash)
		*ret_minor_hash = minor_hash;
	return 0;
}
