has_part_signature(struct mac_partition *p)
{
	return	be16_to_cpu(p->signature) == MAC_PARTITION_MAGIC ||
		be16_to_cpu(p->signature) == MAC_PARTITION_MAGIC_OLD;
}
