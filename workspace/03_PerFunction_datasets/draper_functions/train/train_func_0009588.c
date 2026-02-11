blkid_probe_sprintf_uuid(blkid_probe pr, unsigned char *uuid,
				size_t len, const char *fmt, ...)
{
	struct blkid_chain *chn = blkid_probe_get_chain(pr);
	int rc = -1;
	va_list ap;

	if (len > BLKID_PROBVAL_BUFSIZ)
		len = BLKID_PROBVAL_BUFSIZ;

	if (uuid_is_empty(uuid, len))
		return 0;

	if ((chn->flags & BLKID_SUBLKS_UUIDRAW) &&
	    blkid_probe_set_value(pr, "UUID_RAW", uuid, len) < 0)
		return -1;
	if (!(chn->flags & BLKID_SUBLKS_UUID))
		return 0;

	va_start(ap, fmt);
	rc = blkid_probe_vsprintf_value(pr, "UUID", fmt, ap);
	va_end(ap);


	if (!rc) {
		size_t i;
		struct blkid_prval *v = __blkid_probe_get_value(pr,
						blkid_probe_numof_values(pr));
		if (v) {
			for (i = 0; i < v->len; i++)
				if (v->data[i] >= 'A' && v->data[i] <= 'F')
					v->data[i] = (v->data[i] - 'A') + 'a';
		}
	}
	return rc;
}
