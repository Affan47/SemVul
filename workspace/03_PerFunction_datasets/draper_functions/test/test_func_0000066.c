sha1_object(const void *data, unsigned long size,
			enum object_type type, unsigned char *sha1)
{
	hash_sha1_file(data, size, typename(type), sha1);
	if (has_sha1_file(sha1)) {
		void *has_data;
		enum object_type has_type;
		unsigned long has_size;
		has_data = read_sha1_file(sha1, &has_type, &has_size);
		if (!has_data)
			die("cannot read existing object %s", sha1_to_hex(sha1));
		if (size != has_size || type != has_type ||
		    memcmp(data, has_data, size) != 0)
			die("SHA1 COLLISION FOUND WITH %s !", sha1_to_hex(sha1));
		free(has_data);
	}
}
