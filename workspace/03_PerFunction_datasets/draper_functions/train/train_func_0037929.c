blkid_probe_sprintf_uuid(blkid_probe pr, unsigned char *uuid,
				size_t len, const char *fmt, ...)
{
	struct blkid_chain *chn = blkid_probe_get_chain(pr);
	va_list ap;
	int rc = 0;

	if (blkid_uuid_is_empty(uuid, len))
		return 0;

	if ((chn->flags & BLKID_SUBLKS_UUIDRAW) &&
	    (rc = blkid_probe_set_value(pr, "UUID_RAW", uuid, len)) < 0)
		return rc;

	if (!(chn->flags & BLKID_SUBLKS_UUID))
		return 0;

	va_start(ap, fmt);
	rc = blkid_probe_vsprintf_value(pr, "UUID", fmt, ap);
	va_end(ap);

	return rc;
}
