blkid_probe_set_label(blkid_probe pr, unsigned char *label, size_t len)
{
	struct blkid_chain *chn = blkid_probe_get_chain(pr);
	struct blkid_prval *v;
	if (len > BLKID_PROBVAL_BUFSIZ)
		len = BLKID_PROBVAL_BUFSIZ;

	if ((chn->flags & BLKID_SUBLKS_LABELRAW) &&
	    blkid_probe_set_value(pr, "LABEL_RAW", label, len) < 0)
		return -1;
	if (!(chn->flags & BLKID_SUBLKS_LABEL))
		return 0;
	v = blkid_probe_assign_value(pr, "LABEL");
	if (!v)
		return -1;

	if (len == BLKID_PROBVAL_BUFSIZ)
		len--;

	memcpy(v->data, label, len);
	v->data[len] = '\0';

	v->len = blkid_rtrim_whitespace(v->data) + 1;
	if (v->len == 1)
		blkid_probe_reset_last_value(pr);
	return 0;
}
