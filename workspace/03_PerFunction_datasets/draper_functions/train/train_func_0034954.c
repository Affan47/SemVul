parse_tag(blkid_cache cache, blkid_dev dev, char **cp)
{
	char *name;
	char *value;
	int ret;

	if (!cache || !dev)
		return -BLKID_ERR_PARAM;

	if ((ret = parse_token(&name, &value, cp)) <= 0
)
		return ret;


	if (!strcmp(name, "DEVNO"))
		dev->bid_devno = STRTOULL(value, 0, 0);
	else if (!strcmp(name, "PRI"))
		dev->bid_pri = strtol(value, 0, 0);
	else if (!strcmp(name, "TIME"))
		dev->bid_time = STRTOULL(value, 0, 0);
	else
		ret = blkid_set_tag(dev, name, value, strlen(value));

	DBG(DEBUG_READ, printf("    tag: %s=\"%s\"\n", name, value));

	return ret < 0 ? ret : 1;
}
