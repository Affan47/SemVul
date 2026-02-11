volume_id_probe_linux_raid(struct volume_id *id , uint64_t size)
{
	typedef uint32_t aliased_uint32_t FIX_ALIASING;
#define off ((uint64_t)0)
	uint64_t sboff;
	uint8_t uuid[16];
	struct mdp_super_block *mdp;

	dbg("probing at offset 0x%llx, size 0x%llx",
	    (unsigned long long) off, (unsigned long long) size);

	if (size < 0x10000)
		return -1;

	sboff = (size & ~(MD_RESERVED_BYTES - 1)) - MD_RESERVED_BYTES;
	mdp = volume_id_get_buffer(id, off + sboff, 0x800);
	if (mdp == NULL)
		return -1;

	if (mdp->md_magic != cpu_to_le32(MD_MAGIC))
		return -1;

	*(aliased_uint32_t*)uuid = mdp->set_uuid0;
	memcpy(&uuid[4], &mdp->set_uuid1, 12);
	volume_id_set_uuid(id, uuid, UUID_DCE);


	dbg("found raid signature");


	return 0;
}
