f2fs_dentry_hash(const struct qstr *name_info,
				struct f2fs_filename *fname)
{
	__u32 hash;
	f2fs_hash_t f2fs_hash;
	const unsigned char *p;
	__u32 in[8], buf[4];
	const unsigned char *name = name_info->name;
	size_t len = name_info->len;


	if (fname && !fname->disk_name.name)
		return cpu_to_le32(fname->hash);

	if (is_dot_dotdot(name_info))
		return 0;


	buf[0] = 0x67452301;
	buf[1] = 0xefcdab89;
	buf[2] = 0x98badcfe;
	buf[3] = 0x10325476;

	p = name;
	while (1) {
		str2hashbuf(p, len, in, 4);
		TEA_transform(buf, in);
		p += 16;
		if (len <= 16)
			break;
		len -= 16;
	}
	hash = buf[0];
	f2fs_hash = cpu_to_le32(hash & ~F2FS_HASH_COL_BIT);
	return f2fs_hash;
}
