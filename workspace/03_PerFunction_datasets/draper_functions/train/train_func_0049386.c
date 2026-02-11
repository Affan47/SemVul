read_pte(struct fdisk_context *cxt, size_t pno, fdisk_sector_t offset)
{
	int rc;
	unsigned char *buf;
	struct pte *pe = self_pte(cxt, pno);

	buf = calloc(1, cxt->sector_size);
	if (!buf)
		return -ENOMEM;

	DBG(LABEL, ul_debug("DOS: reading EBR %zu: offset=%ju, buffer=%p",
				pno, (uintmax_t) offset, buf));

	pe->offset = offset;
	pe->sectorbuffer = buf;
	pe->private_sectorbuffer = 1;

	rc = read_sector(cxt, offset, pe->sectorbuffer);
	if (rc) {
		fdisk_warn(cxt, _("Failed to read extended partition table "
				"(offset=%ju)"), (uintmax_t) offset);
		return rc;
	}

	pe->changed = 0;
	pe->pt_entry = pe->ex_entry = NULL;
	return 0;
}
