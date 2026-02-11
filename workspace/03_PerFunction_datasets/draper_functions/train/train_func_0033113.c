probe_nvraid(blkid_probe pr,
		const struct blkid_idmag *mag __attribute__((__unused__)))
{
	uint64_t off;
	struct nv_metadata *nv;

	if (pr->size < 0x10000)
		return -1;
	if (!S_ISREG(pr->mode) && !blkid_probe_is_wholedisk(pr))
		return -1;

	off = ((pr->size / 0x200) - 2) * 0x200;
	nv = (struct nv_metadata *)
		blkid_probe_get_buffer(pr,
				off,
				sizeof(struct nv_metadata));
	if (!nv)
		return -1;

	if (memcmp(nv->vendor, NVIDIA_SIGNATURE, sizeof(NVIDIA_SIGNATURE)-1) != 0)
		return -1;
	if (blkid_probe_sprintf_version(pr, "%u", le16_to_cpu(nv->version)) != 0)
		return -1;
	if (blkid_probe_set_magic(pr, off, sizeof(nv->vendor),
				(unsigned char *) nv->vendor))
		return -1;
	return 0;
}
