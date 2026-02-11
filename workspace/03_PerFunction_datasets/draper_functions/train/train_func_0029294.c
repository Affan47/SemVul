probe_raid1(blkid_probe pr, off_t off)
{
	struct mdp1_super_block *mdp1;

	mdp1 = (struct mdp1_super_block *)
			blkid_probe_get_buffer(pr,
				off,
				sizeof(struct mdp1_super_block));
	if (!mdp1)
		return -1;
	if (le32_to_cpu(mdp1->magic) != MD_SB_MAGIC)
		return -1;
	if (le32_to_cpu(mdp1->major_version) != 1U)
		return -1;
	if (le64_to_cpu(mdp1->super_offset) != (uint64_t) off >> 9)
		return -1;
	if (blkid_probe_set_uuid(pr, (unsigned char *) mdp1->set_uuid) != 0)
		return -1;
	if (blkid_probe_set_uuid_as(pr,
			(unsigned char *) mdp1->device_uuid, "UUID_SUB") != 0)
		return -1;
	if (blkid_probe_set_label(pr, mdp1->set_name,
				sizeof(mdp1->set_name)) != 0)
		return -1;
	if (blkid_probe_set_magic(pr, off, sizeof(mdp1->magic),
				(unsigned char *) &mdp1->magic))
		return -1;
	return 0;
}
