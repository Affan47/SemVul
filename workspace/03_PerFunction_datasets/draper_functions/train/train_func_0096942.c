image_hash_from_data(struct image * image) {

	unsigned char buf[0x20000];
	uint16_t hash = 0;
	int ret;

	image_seek(image, 0);
	while ( ( ret = image_read(image, &buf, sizeof(buf)) ) )
		hash ^= do_hash((uint16_t *)&buf, ret);

	return hash;
}
