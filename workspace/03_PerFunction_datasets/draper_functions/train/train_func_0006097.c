indi_find_dev_cb(struct indi_t *indi, const char *devname)
{
	indi_list *isl;

	for (isl = il_iter(indi->dev_cb_list); ! il_is_last(isl); isl = il_next(isl)) {
		struct indi_dev_cb_t *cb = (struct indi_dev_cb_t *)il_item(isl);
		if (strlen(cb->devname) == 0 || strncmp(cb->devname, devname, sizeof(cb->devname)) == 0) {
			return cb;
		}
	}
	return NULL;
}
