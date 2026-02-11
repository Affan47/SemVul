blkid_dev_has_tag(blkid_dev dev, const char *type,
			     const char *value)
{
	blkid_tag		tag;

	tag = blkid_find_tag_dev(dev, type);
	if (!value)
		return (tag != NULL);
	if (!tag || strcmp(tag->bit_val, value))
		return 0;
	return 1;
}
