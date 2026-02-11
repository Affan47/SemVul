match_dev_by_uuid(struct device *dev, const void *data)
{
	const struct uuidcmp *cmp = data;
	struct hd_struct *part = dev_to_part(dev);

	if (!part->info)
		goto no_match;

	if (strncasecmp(cmp->uuid, part->info->uuid, cmp->len))
		goto no_match;

	return 1;
no_match:
	return 0;
}
