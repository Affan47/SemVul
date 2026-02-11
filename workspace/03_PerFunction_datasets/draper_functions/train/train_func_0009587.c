verify_tag(const char *devname, const char *name, const char *value)
{
	blkid_probe pr;
	int fd = -1, rc = -1;
	size_t len;
	const char *data;
	int errsv = 0;

	pr = blkid_new_probe();
	if (!pr)
		return -1;

	blkid_probe_enable_superblocks(pr, TRUE);
	blkid_probe_set_superblocks_flags(pr,
			BLKID_SUBLKS_LABEL | BLKID_SUBLKS_UUID);

	fd = open(devname, O_RDONLY);
	if (fd < 0) {
		errsv = errno;
		goto done;
	}
	if (blkid_probe_set_device(pr, fd, 0, 0))
		goto done;
	rc = blkid_do_safeprobe(pr);
	if (rc)
		goto done;
	rc = blkid_probe_lookup_value(pr, name, &data, &len);
	if (!rc)
		rc = memcmp(value, data, len);
done:
	DBG(DEBUG_EVALUATE, printf("%s: %s verification %s\n",
			devname, name, rc == 0 ? "PASS" : "FAILED"));
	if (fd >= 0)
		close(fd);
	blkid_free_probe(pr);


	return errsv == EACCES ? 0 : rc;
}
