parse_dev(blkid_cache cache, blkid_dev *dev, char **cp)
{
	char *start, *tmp, *end, *name;
	int ret;

	if ((ret = parse_start(cp)) <= 0)
		return ret;

	start = tmp = strchr(*cp, '>');
	if (!start) {
		DBG(DEBUG_READ,
		    printf("blkid: short line parsing dev: %s\n", *cp));
		return -BLKID_ERR_CACHE;
	}
	start = skip_over_blank(start + 1);
	end = skip_over_word(start);

	DBG(DEBUG_READ, printf("device should be %*s\n",
			       (int)(end - start), start));

	if (**cp == '>')
		*cp = end;
	else
		(*cp)++;

	*tmp = '\0';

	if (!(tmp = strrchr(end, '<')) || parse_end(&tmp) < 0) {
		DBG(DEBUG_READ,
		    printf("blkid: missing </device> ending: %s\n", end));
	} else if (tmp)
		*tmp = '\0';

	if (end - start <= 1) {
		DBG(DEBUG_READ, printf("blkid: empty device name: %s\n", *cp));
		return -BLKID_ERR_CACHE;
	}

	name = blkid_strndup(start, end-start);
	if (name == NULL)
		return -BLKID_ERR_MEM;

	DBG(DEBUG_READ, printf("found dev %s\n", name));

	if (!(*dev = blkid_get_dev(cache, name, BLKID_DEV_CREATE))) {
		free(name);
		return -BLKID_ERR_MEM;
	}

	free(name);
	return 1;
}
