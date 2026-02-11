blkid_debug_dump_tag(blkid_tag tag)
{
	if (!tag) {
		fprintf(stderr, "    tag: NULL\n");
		return;
	}

	fprintf(stderr, "    tag: %s=\"%s\"\n", tag->bit_name, tag->bit_val);
}
