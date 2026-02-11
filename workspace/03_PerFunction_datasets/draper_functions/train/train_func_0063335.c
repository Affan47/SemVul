fdisk_next_label(struct fdisk_context *cxt, struct fdisk_label **lb)
{
	size_t i;
	struct fdisk_label *res = NULL;

	if (!lb || !cxt)
		return -EINVAL;

	if (!*lb)
		res = cxt->labels[0];
	else {
		for (i = 1; i < cxt->nlabels; i++) {
			if (*lb == cxt->labels[i - 1]) {
				res = cxt->labels[i];
				break;
			}
		}
	}

	*lb = res;
	return res ? 0 : 1;
}
